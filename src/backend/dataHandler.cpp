//===== ===== Extern ===== =====
#include <cassert>
#include <string>
#include <iostream>

//===== ===== Intern ===== =====
#include "dataHandler.h"

#include <csv_parser.hpp>
#include <string>
#include <tuple>
#include "../utility/types_parser.hpp"
#include "../utility/stringCollection.h"

static std::map<uint64_t, std::tuple<bool, std::string, sexType, std::tm, std::string, std::tm, std::string, std::string>> tmp_table_peoples;
static std::map<uint64_t, std::tuple<size_t, bool, std::string>> tmp_table_titles;
static std::map<uint64_t, std::tuple<size_t, bool, std::string>> tmp_table_firstnames;
static std::map<uint64_t, std::tuple<size_t, bool, std::string>> tmp_table_lastnames;
static std::map<uint64_t, std::tuple<size_t, bool, relType>> tmp_table_bloodlines;
static std::map<uint64_t, std::tuple<size_t, bool, relType, std::tm, std::tm>> tmp_table_relationships;

/// <summary>
/// Table types [x] <- is key
/// [int], bool, string, sexType, tm, string, tm, string, string
/// feads into the suffix, sex, birthday, placeOfBirth, death, placeOfDeath, remarks vector in the personInfos struct
/// </summary>
static void InitPeoplesTable(std::ifstream& peoples);

/// <summary>
/// Table types [x] <- is key
/// [int, int], bool, string
/// feads into the titles vector in the personInfos struct
/// </summary>
static void InitTitlesTable(std::ifstream& peoples);

/// <summary>
/// Table types [x] <- is key
/// [int, int], bool, string
/// feads into the firstNames vector in the personInfos struct
/// </summary>
static void InitFirstNamesTable(std::ifstream& peoples);

/// <summary>
/// Table types [x] <- is key
/// [int, int], bool, string
/// feads into the lastNames vector in the personInfos struct
/// </summary>
static void InitLastNamesTable(std::ifstream& peoples);

/// <summary>
/// Table types [x] <- is key
/// [int, int], bool, relType
/// feads into the blood struct
/// </summary>
static void InitBloodLinesTable(std::ifstream& peoples);

/// <summary>
/// Table types [x] <- is key
/// [int, int], bool, relType, tm, tm
/// feads into the relation struct
/// </summary>
static void InitRelationshipsTable(std::ifstream& peoples);

static void BuildTables(void);

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

		BuildTables();
	}

	std::pair<std::set<blood>, std::set<relation>> GetRelations(const int rootID/* = 0*/, const int dinst/* = -1*/) {
		assert(false && "not implimented");
		return std::pair<std::set<blood>, std::set<relation>>();
	}

	personInfos GetPerson(const int personID) {
		assert(false && "not implimented");
		return personInfos();
	}
}

static void InitPeoplesTable(std::ifstream& peoples) {
	// fist line sould look like this:
	// ID,CONFIDENTIAL,NAME_SUFFIX,SEX,BIRTHDAY,PLACE_OF_BIRTH,DEATH,PLACE_OF_DEATH,REMARKS

	std::string line;

	// first line
	if (!std::getline(peoples, line)) {
		std::cerr << "error: reading fist line in " FILE_PEOPLES "\n";
	}

	// IGNORE fist line
	//if (line != "ID,CONFIDENTIAL,NAME_SUFFIX,SEX,BIRTHDAY,PLACE_OF_BIRTH,DEATH,PLACE_OF_DEATH,REMARKS") {
		//std::cerr << "error: fist line in Peoples.csv not 'ID,CONFIDENTIAL,NAME_SUFFIX,SEX,BIRTHDAY,PLACE_OF_BIRTH,DEATH,PLACE_OF_DEATH,REMARKS'\n";
		//return;
	//}

	while (std::getline(peoples, line)) {
		auto ret = csv_parser::parse_line<
			uint64_t,
			bool,
			std::string,
			sexType,
			std::tm, std::string,
			std::tm, std::string,
			std::string>(line);

		tmp_table_peoples[std::get<0>(ret)] = std::make_tuple(
			std::get<1>(ret),
			std::get<2>(ret),
			std::get<3>(ret),
			std::get<4>(ret),
			std::get<5>(ret),
			std::get<6>(ret),
			std::get<7>(ret),
			std::get<8>(ret)
		);
	}
}

static void InitTitlesTable(std::ifstream& titles) {
	std::string line;

	// first line
	if (!std::getline(titles, line)) {
		std::cerr << "error: reading fist line in " FILE_TITLES "\n";
	}

	// IGNORE fist line

	while (std::getline(titles, line)) {
		auto ret = csv_parser::parse_line<
			uint64_t,
			uint64_t,
			bool,
			std::string>(line);

		tmp_table_titles[std::get<0>(ret)] = std::make_tuple(
			std::get<1>(ret),
			std::get<2>(ret),
			std::get<3>(ret)
		);
	}
}

static void InitFirstNamesTable(std::ifstream& firstnames) {
	std::string line;

	// first line
	if (!std::getline(firstnames, line)) {
		std::cerr << "error: reading fist line in " FILE_FIRSTNAMES "\n";
	}

	// IGNORE fist line

	while (std::getline(firstnames, line)) {
		auto ret = csv_parser::parse_line<
			uint64_t,
			uint64_t,
			bool,
			std::string>(line);

		tmp_table_firstnames[std::get<0>(ret)] = std::make_tuple(
			std::get<1>(ret),
			std::get<2>(ret),
			std::get<3>(ret)
		);
	}
}

static void InitLastNamesTable(std::ifstream& lastnames) {
	std::string line;

	// first line
	if (!std::getline(lastnames, line)) {
		std::cerr << "error: reading fist line in " FILE_LASTNAMES "\n";
	}

	// IGNORE fist line

	while (std::getline(lastnames, line)) {
		auto ret = csv_parser::parse_line<
			uint64_t,
			uint64_t,
			bool,
			std::string>(line);

		tmp_table_lastnames[std::get<0>(ret)] = std::make_tuple(
			std::get<1>(ret),
			std::get<2>(ret),
			std::get<3>(ret)
		);
	}
}

static void InitBloodLinesTable(std::ifstream& bloodlines) {
	std::string line;

	// first line
	if (!std::getline(bloodlines, line)) {
		std::cerr << "error: reading fist line in " FILE_BLOODLINES "\n";
	}

	// IGNORE fist line

	while (std::getline(bloodlines, line)) {
		auto ret = csv_parser::parse_line<
			uint64_t,
			uint64_t,
			bool,
			relType>(line);

		tmp_table_bloodlines[std::get<0>(ret)] = std::make_tuple(
			std::get<1>(ret),
			std::get<2>(ret),
			std::get<3>(ret)
		);
	}
}

static void InitRelationshipsTable(std::ifstream& relationships) {
	std::string line;

	// first line
	if (!std::getline(relationships, line)) {
		std::cerr << "error: reading fist line in " FILE_RELATIONSHIPS "\n";
	}

	// IGNORE fist line

	while (std::getline(relationships, line)) {
		auto ret = csv_parser::parse_line<
			uint64_t,
			uint64_t,
			bool,
			relType,
			std::tm,
			std::tm>(line);

		tmp_table_relationships[std::get<0>(ret)] = std::make_tuple(
			std::get<1>(ret),
			std::get<2>(ret),
			std::get<3>(ret),
			std::get<4>(ret),
			std::get<5>(ret)
		);
	}
}

static void BuildTables(void) {
}

