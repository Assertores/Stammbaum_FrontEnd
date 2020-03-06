//===== ===== Extern ===== =====
#include <cassert>
#include <string>
#include <tuple>
#include <iostream>
#include <unordered_map>
#include <algorithm>

//===== ===== Intern ===== =====
#include "dataHandler.h"

#include <csv_parser.hpp>

#include "../utility/types_parser.hpp"
#include "../utility/stringCollection.h"

static std::map<uint64_t, std::tuple<size_t, bool, relType>> tmp_table_bloodlines;
static std::map<uint64_t, std::tuple<size_t, bool, relType, std::tm, std::tm>> tmp_table_relationships;

static std::unordered_map<uint64_t, personInfos> persons_table;
static std::map<std::pair<int, int>, relType> bloodlines_table;
static std::map < std::pair<int, int>, std::tuple<relType, std::tm, std::tm>> relationships_table;

/*!
 * @brief	Table types [x] <- is key
 *			[int], bool, string, sexType, tm, string, tm, string, string
 *			feads into the suffix, sex, birthday, placeOfBirth, death, placeOfDeath, remarks vector in the personInfos struct
 */
void InitPeoplesTable(std::ifstream& peoples);

/*!
 * @brief	Table types [x] <- is key
 *			[int, int], bool, string
 *			feads into the titles vector in the personInfos struct
 */
void InitTitlesTable(std::ifstream& peoples);

/*!
 * @brief	Table types [x] <- is key
 *			[int, int], bool, string
 *			feads into the firstNames vector in the personInfos struct
 */
void InitFirstNamesTable(std::ifstream& peoples);

/*!
 * @brief	Table types [x] <- is key
 *			[int, int], bool, string
 *			feads into the lastNames vector in the personInfos struct
 */
void InitLastNamesTable(std::ifstream& peoples);

/*!
 * @brief	Table types [x] <- is key
 *			[int, int], bool, relType
 *			feads into the blood struct
 */
void InitBloodLinesTable(std::ifstream& peoples);

/*!
 * @brief	Table types [x] <- is key
 *			[int, int], bool, relType, tm, tm
 *			feads into the relation struct
 */
void InitRelationshipsTable(std::ifstream& peoples);

namespace dataHandler {
	void InitTables(std::ifstream& peoples, std::ifstream& titles, std::ifstream& firstNames, std::ifstream& lastNames, std::ifstream& bloodLines, std::ifstream& relationships) {
		assert(!peoples.fail());
		assert(!titles.fail());
		assert(!firstNames.fail());
		assert(!lastNames.fail());
		assert(!bloodLines.fail());
		assert(!relationships.fail());

		InitPeoplesTable(peoples);
		InitTitlesTable(titles);
		InitFirstNamesTable(firstNames);
		InitLastNamesTable(lastNames);
		InitBloodLinesTable(bloodLines);
		InitRelationshipsTable(relationships);
	}

	std::pair<std::set<blood>, std::set<relation>> GetRelations(const int rootID/* = 0*/, const int dinst/* = -1*/) {

		std::set<int> personIDs;
		personIDs.insert(rootID);
		std::set<blood> relevantBloodlines;
		std::set<relation> relevantRelations;

		for(int i = 0; i < dinst; i++) {

			std::set<int> newIDs;
			for(auto& it : bloodlines_table) {
				for(auto& currentID : personIDs) {
					if(it.first.first == currentID ||
					   it.first.second == currentID) {
						relevantBloodlines.emplace(blood {
							(int)it.first.first,
							(int)it.first.second,
							it.second,
						});

						newIDs.insert((int)it.first.first);
						newIDs.insert((int)it.first.second);
					}
				}
			}

			for(auto& it : relationships_table) {
				for(auto& currentID : personIDs) {
					if(it.first.first == currentID ||
					   it.first.second == currentID) {
						relevantRelations.emplace(relation {
							(int)it.first.first,
							(int)it.first.second,
							std::get<0>(it.second),
							std::get<1>(it.second),
							std::get<2>(it.second),
						});

						newIDs.insert((int)it.first.first);
						newIDs.insert((int)it.first.second);
					}
				}
			}

			personIDs.merge(newIDs);
		}


		return std::pair(relevantBloodlines, relevantRelations);
	}

	personInfos GetPerson(const int personID) {
		//assert(false && "not implimented");
		if(persons_table.count(personID)) {
			return persons_table[personID];
		}
		return personInfos();
	}
}

static void InitPeoplesTable(std::ifstream& peoples) {
	// fist line sould look like this:
	// ID,CONFIDENTIAL,NAME_SUFFIX,SEX,BIRTHDAY,PLACE_OF_BIRTH,DEATH,PLACE_OF_DEATH,REMARKS

	std::string line;

	// first line
	if(!std::getline(peoples, line)) {
		std::cerr << "error: reading fist line in " FILE_PEOPLES "\n";
	}

	// IGNORE fist line
	//if (line != "ID,CONFIDENTIAL,NAME_SUFFIX,SEX,BIRTHDAY,PLACE_OF_BIRTH,DEATH,PLACE_OF_DEATH,REMARKS") {
		//std::cerr << "error: fist line in Peoples.csv not 'ID,CONFIDENTIAL,NAME_SUFFIX,SEX,BIRTHDAY,PLACE_OF_BIRTH,DEATH,PLACE_OF_DEATH,REMARKS'\n";
		//return;
	//}

	while(std::getline(peoples, line)) {
		auto ret = csv_parser::parse_line<
			uint64_t,
			bool,
			std::string,
			sexType,
			std::tm, std::string,
			std::tm, std::string,
			std::string>(line);

		auto& person = persons_table[std::get<0>(ret)];

		// TODO: handle confidential = std::get<1>(ret)
		person.id = std::get<0>(ret);
		person.suffix = std::get<2>(ret);
		person.sex = std::get<3>(ret);
		person.birthday = std::get<4>(ret);
		person.placeOfBirth = std::get<5>(ret);
		person.death = std::get<6>(ret);
		person.placeOfDeath = std::get<7>(ret);
		person.remarks = std::get<8>(ret);

		// TODO: determain use case
		person.suffix.shrink_to_fit();
		person.placeOfBirth.shrink_to_fit();
		person.placeOfDeath.shrink_to_fit();
		person.remarks.shrink_to_fit();
	}
}

static void InitTitlesTable(std::ifstream& titles) {
	std::string line;

	// first line
	if(!std::getline(titles, line)) {
		std::cerr << "error: reading fist line in " FILE_TITLES "\n";
	}

	// IGNORE fist line

	while(std::getline(titles, line)) {
		auto ret = csv_parser::parse_line<
			uint64_t,
			uint64_t,
			bool,
			std::string>(line);

		// TODO: confidential

		// get person
		if(!persons_table.count(std::get<0>(ret))) {
			std::cerr << "error: titles contain entry for non existent personID '" << std::get<0>(ret) << "'\n";
		}

		auto& person = persons_table[std::get<0>(ret)];
		// TODO: some how ensure the order of titles
		person.titles.emplace_back(std::get<3>(ret));
	}
}

static void InitFirstNamesTable(std::ifstream& firstnames) {
	std::string line;

	// first line
	if(!std::getline(firstnames, line)) {
		std::cerr << "error: reading fist line in " FILE_FIRSTNAMES "\n";
	}

	// IGNORE fist line

	while(std::getline(firstnames, line)) {
		auto ret = csv_parser::parse_line<
			uint64_t,
			uint64_t,
			bool,
			std::string>(line);

		// TODO: confidential

		// get person
		if(!persons_table.count(std::get<0>(ret))) {
			std::cerr << "error: firstNames contain entry for non existent personID '" << std::get<0>(ret) << "'\n";
		}

		auto& person = persons_table[std::get<0>(ret)];
		// TODO: some how ensure the order of names
		person.firstNames.emplace_back(std::get<3>(ret));
	}
}

static void InitLastNamesTable(std::ifstream& lastnames) {
	std::string line;

	// first line
	if(!std::getline(lastnames, line)) {
		std::cerr << "error: reading fist line in " FILE_LASTNAMES "\n";
	}

	// IGNORE fist line

	while(std::getline(lastnames, line)) {
		auto ret = csv_parser::parse_line<
			uint64_t,
			uint64_t,
			bool,
			std::string>(line);

		// TODO: confidential

		// get person
		if(!persons_table.count(std::get<0>(ret))) {
			std::cerr << "error: lastNames contain entry for non existent personID '" << std::get<0>(ret) << "'\n";
		}

		auto& person = persons_table[std::get<0>(ret)];
		// TODO: some how ensure the order of names
		person.lastNames.emplace_back(std::get<3>(ret));
	}
}

static void InitBloodLinesTable(std::ifstream& bloodlines) {
	std::string line;

	// first line
	if(!std::getline(bloodlines, line)) {
		std::cerr << "error: reading fist line in " FILE_BLOODLINES "\n";
	}

	// IGNORE fist line

	while(std::getline(bloodlines, line)) {
		auto ret = csv_parser::parse_line<
			uint64_t,
			uint64_t,
			bool,
			relType>(line);

		// TODO: confidential

		bloodlines_table[std::pair(std::get<0>(ret), std::get<1>(ret))] = std::get<3>(ret);

#if Obsolete
		tmp_table_bloodlines[std::get<0>(ret)] = std::make_tuple(
			std::get<1>(ret),
			std::get<2>(ret),
			std::get<3>(ret)
		);
#endif
	}
}

static void InitRelationshipsTable(std::ifstream& relationships) {
	std::string line;

	// first line
	if(!std::getline(relationships, line)) {
		std::cerr << "error: reading fist line in " FILE_RELATIONSHIPS "\n";
	}

	// IGNORE fist line

	while(std::getline(relationships, line)) {
		auto ret = csv_parser::parse_line<
			uint64_t,
			uint64_t,
			bool,
			relType,
			std::tm,
			std::tm>(line);

		// TODO: confidential

		relationships_table[std::pair(std::get<0>(ret), std::get<1>(ret))] = std::make_tuple(
			std::get<3>(ret),
			std::get<4>(ret),
			std::get<5>(ret)
		);

#if Obsolete
		tmp_table_relationships[std::get<0>(ret)] = std::make_tuple(
			std::get<1>(ret),
			std::get<2>(ret),
			std::get<3>(ret),
			std::get<4>(ret),
			std::get<5>(ret)
		);
#endif
	}
}

