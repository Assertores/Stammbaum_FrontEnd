#include <iomanip>

#include "printer.h"

std::ostream& operator<<(std::ostream& os, const std::chrono::system_clock::time_point& time) {
	std::time_t tt = std::chrono::system_clock::to_time_t(time);
	return os << std::put_time(std::localtime(&tt), "%d.%m.%Y");
}

std::ostream& operator<<(std::ostream& os, const std::tm& time) {
	if(time.tm_mon < 0 || time.tm_mon > 12 ||
	   time.tm_mday < 0 || time.tm_mday > 33)
		return os << "NAN";

	return os << std::put_time(&time, "%d.%m.%Y");
}

cString relToString(const relType t) {
	switch(t) {
	case Father:
		return "Father";
	case Mother:
		return "Mother";
	case FosterMother:
		return "Foster Mother";
	case Married:
		return "Married";
	default:
		return "Relation not found";
	}
}

char relToChar(const relType t) {
	switch(t) {
	case Father:
		return 'F';
	case Mother:
		return 'M';
	case FosterMother:
		return 'm';
	case Married:
		return '⚭';
	default:
		return '#';
	}
}

cString sexToString(const sexType t) {
	switch(t) {
	case Male:
		return "Male";
	case Female:
		return "Female";
	case Deverce:
		return "Deverce";
	default:
		return "Sex not found";
	}
}

char sexToChar(const sexType t) {
	switch(t) {
	case Male:
		return 'M'/*'♂'*/;
	case Female:
		return 'F'/*'♀'*/;
	case Deverce:
		return 'D'/*'⚥'*/;
	default:
		return '#';
	}
}

//┌──────────────────┴───────────────────┐
//│Prof. Andreas E. F. von und zu Edmeier│
//│   ♂ | * 20.01.2020 | + 20.01.2020    │
//└──────────────────┬───────────────────┘
std::string PersonToString(const personInfos person, bool longVariant/* = true*/) {
	std::stringstream value;

	if(person.titles.size() > 0) {
		if(longVariant) {
			for(size_t i = 0; i < person.titles.size(); i++) {
				value << person.titles[i] << " ";
			}
		} else {
			value << person.titles[0] << " ";
		}
	}

	if(person.firstNames.size() <= 0) {
		value << "NAN ";
	} else {
		value << person.firstNames[0] << " ";

		if(person.firstNames.size() > 1) {
			if(longVariant)
				value << "(";

			for(size_t i = 1; i < person.firstNames.size() - 1; i++) {
				if(longVariant)
					value << person.firstNames[i] << ", ";
				else
					value << person.firstNames[i][0] << ". ";
			}
			if(longVariant)
				value << person.firstNames[person.firstNames.size() - 1] << ")" << std::endl;
			else
				value << person.firstNames[person.firstNames.size() - 1][0] << ". ";
		}

	}

	if(!person.suffix.empty())
		value << person.suffix << " ";

	if(person.lastNames.size() <= 0) {
		value << "NAN";
	} else {
		if(longVariant && person.lastNames.size() > 1) {
			value << "(";
			for(size_t i = 0; i < person.lastNames.size() - 2; i++) {
				value << person.lastNames[i] << ", ";
			}
			value << person.lastNames[person.lastNames.size() - 2] << ") ";
		}

		value << person.lastNames[person.lastNames.size() - 1];
	}
	value << std::endl;

	if(longVariant)
		value << "Sex: " << sexToString(person.sex) << std::endl;
	else
		value << sexToChar(person.sex) << " | ";

	if(longVariant) {
		value << "B-day: " << person.birthday;
		if(!person.placeOfBirth.empty())
			value << " at: " << person.placeOfBirth;
		value << std::endl;
	} else {
		value << "* " << person.birthday << " | ";
	}

	if(longVariant) {
		value << "Death: " << person.death;
		if(!person.placeOfDeath.empty())
			value << " at: " << person.placeOfDeath;
	} else {
		value << "+ " << person.death;
	}

	if(longVariant && !person.remarks.empty())
		value << std::endl << "Remarks:" << std::endl << person.remarks;

	return value.str();
}

inline bool IsAConnection(std::pair<std::set<int>, std::set<int>>& allConnections, int key) {
	if(allConnections.first.find(key) != allConnections.first.end())
		return true;
	return allConnections.second.find(key) != allConnections.second.end();
}

inline bool IsConnectionUpper(std::pair<std::set<int>, std::set<int>>& allConnections, int key) {
	return allConnections.first.find(key) != allConnections.first.end();
}

std::string PlumbGeneration(std::vector<std::pair<std::set<int>, std::set<int>>>& families) {
	std::string value;

	std::pair<std::set<int>, std::set<int>> prevfam; //previous families
	std::pair<std::set<int>, std::set<int>> allCon; //all connections
	int maxLength = -1;

	for(size_t i = 0; i < families.size(); i++) {
		for(auto& it : families[i].first) {
			allCon.first.emplace(it);
			maxLength = maxLength > it ? maxLength : it;
		}

		for(auto& it : families[i].second) {
			allCon.second.emplace(it);
			maxLength = maxLength > it ? maxLength : it;
		}
	}

	//===== ===== drawing top spacing ===== =====
	int lastPos = 0;
	for(auto& it : allCon.first) {
		value.append(it - lastPos - 1, ' ');
		value.append(1, '|');
		lastPos = it;
	}
	value.append(1, '\n');

	for(size_t currentFamilie = 0; currentFamilie < families.size(); currentFamilie++) {
		int max = *(families[currentFamilie].first.rbegin());//families[currentFamilie].first.rbegin() > families[currentFamilie].second.rbegin() ? families[currentFamilie].first.rbegin() : families[currentFamilie].second.rbegin();
		max = max > * (families[currentFamilie].second.rbegin()) ? max : *(families[currentFamilie].second.rbegin());
		bool inFamilie = false;

		for(int i = 1; i <= maxLength; i++) {
			if(IsAConnection(allCon, i)) {
				if(IsAConnection(families[currentFamilie], i)) {
					value.append(1, '+');
					inFamilie = i < max;
				} else {
					if(IsConnectionUpper(allCon, i)) {
						if(prevfam.first.find(i) != prevfam.first.end()) {
							value.append(1, inFamilie ? '-' : ' ');
						} else {
							value.append(1, '|');
						}
					} else {
						if(prevfam.second.find(i) != prevfam.second.end()) {
							value.append(1, '|');
						} else {
							value.append(1, inFamilie ? '-' : ' ');
						}
					}
				}
			} else {
				value.append(1, inFamilie ? '-' : ' ');
			}
		}
		value.append(1, '\n');
		prevfam.first.merge(families[currentFamilie].first);
		prevfam.second.merge(families[currentFamilie].second);
	}

	//===== ===== drawing bottom spacing ===== =====
	lastPos = 0;
	for(auto& it : allCon.second) {
		value.append(it - lastPos - 1, ' ');
		value.append(1, '|');
		lastPos = it;
	}

	return value;
}


// ┌───┐┌───┐
// │ 0 ││ 1 │
// └─┬─┘└─┬─┘
//   ├──┬─┴─────┐
// ┌─┴─┐│┌───┐┌─┴─┐┌───┐
// │ 2 │││ 3 ││ 4 ││ 5 │
// └─┬─┘│└─┬─┘└─┬─┘└─┬─┘
//   └──│┬─┘    │    │
//   ┌──││──────┴────┘
// ┌─┴─┐││┌───┐
// │ 6 ││││ 7 │
// └─┬─┘││└─┬─┘
//   ├──││──┘
//   │  │└─┐
// ┌─┴─┐│┌─┴─┐
// │ 8 │││ 9 │
// └─┬─┘│└─┬─┘
//   ├──│──┘
//   │  └─┐
// ┌─┴─┐┌─┴─┐┌───┐
// │10 ││11 ││12 │
// └─┬─┘└─┬─┘└─┬─┘
//   └──┬─┤    │
//   ┌──│─┴────┘
// ┌─┴─┐│┌───┐
// │13 │││14 │
// └─┬─┘│└─┬─┘
//   ├──│──┘
//   │  └─┐
// ┌─┴─┐┌─┴─┐
// │15 ││16 │
// └─┬─┘└─┬─┘
//   ├────┘
// ┌─┴─┐
// │17 │
// └───┘

//|      |||       |
//+------+|+-------+
//    |   |    |
//    +---|----+
//    |   +----+
//    |        |
//+------++-------+
//|      ||       |

// ┌─┴─┐ ┌─┴─┐ ┌─┴─┐ ┌─┴─┐
// │   │ │   │ │   │ │   │
// └─┬─┘ └─┬─┘ └─┬─┘ └─┬─┘
//   │     │     └─────┤
//   ├─────┼─────┐     │
// ┌─┴─┐ ┌─┴─┐ ┌─┴─┐ ┌─┴─┐
// │   │ │   │ │   │ │   │
// └─┬─┘ └─┬─┘ └─┬─┘ └─┬─┘
