#include <iomanip>

#include "printer.h"

std::ostream& operator<<(std::ostream & os, const std::chrono::system_clock::time_point& time) {
	std::time_t tt = std::chrono::system_clock::to_time_t(time);
	return os << std::put_time(std::localtime(&tt), "%d.%m.%Y");
}

std::ostream& operator<<(std::ostream& os, const std::tm& time) {
	if(time.tm_mon < 0 || time.tm_mon > 12 ||
	   time.tm_yday < 0 || time.tm_yday > 358)
		return os << "Invalide Date";

	return os << std::put_time(&time, "%d.%m.%Y");
}

cString relToString(relType t) {
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

char relToChar(relType t) {
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

cString sexToString(sexType t) {
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

char sexToChar(sexType t) {
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
std::string PersonToString(personInfos person, bool longVariant/* = true*/) {
	std::stringstream value;

	if(person.titles.size() > 0) {
		if(longVariant) {
			for(int i = 0; i < person.titles.size(); i++) {
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

			for(int i = 1; i < person.firstNames.size() - 1; i++) {
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

	if(person.suffix != nullptr)
		value << person.suffix << " ";

	if(person.firstNames.size() <= 0) {
		value << "NAN";
	} else {
		if(longVariant && person.lastNames.size() > 1) {
			value << "(";
			for(int i = 0; i < person.lastNames.size() - 2; i++) {
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
		if(person.placeOfBirth != nullptr)
			value << " at: " << person.placeOfBirth;
		value << std::endl;
	} else {
		value << "* " << person.birthday << " | ";
	}

	if(longVariant) {
		value << "Death: " << person.death;
		if(person.placeOfDeath != nullptr)
			value << " at: " << person.placeOfDeath;
		value << std::endl;
	} else {
		value << "+ " << person.death;
	}

	if(longVariant && person.remarks != nullptr)
		value << "Remarks:" << std::endl << person.remarks;

	return value.str();
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

// ┌─┴─┐ ┌─┴─┐ ┌─┴─┐ ┌─┴─┐
// │   │ │   │ │   │ │   │
// └─┬─┘ └─┬─┘ └─┬─┘ └─┬─┘
//   │     │     └─────┤
//   ├─────┼─────┐     │
// ┌─┴─┐ ┌─┴─┐ ┌─┴─┐ ┌─┴─┐
// │   │ │   │ │   │ │   │
// └─┬─┘ └─┬─┘ └─┬─┘ └─┬─┘
