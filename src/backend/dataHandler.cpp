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

static std::map<uint64_t, std::tuple<bool, std::string, sexType, std::tm, std::string, std::tm, std::string, std::string>> table_peoples;

/// <summary>
/// Table types
/// int, bool, string, sexType, tm, string, tm, string, string
/// </summary>
static void InitPeoplesTable(std::ifstream& peoples);

/// <summary>
/// Table types
/// int, int, bool, string
/// </summary>
static void InitTitlesTable(std::ifstream& peoples);

/// <summary>
/// Table types
/// int, int, bool, string
/// </summary>
static void InitFirstNamesTable(std::ifstream& peoples);

/// <summary>
/// Table types
/// int, int, bool, string
/// </summary>
static void InitLastNamesTable(std::ifstream& peoples);

/// <summary>
/// Table types
/// int, int, bool, relType
/// </summary>
static void InitBloodLinesTable(std::ifstream& peoples);

/// <summary>
/// Table types
/// int, int, bool, relType, tm, tm
/// </summary>
static void InitRelationshipsTable(std::ifstream& peoples);

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
		std::cerr << "error: reading fist line in Peoples.csv\n";
	}

	if (line != "ID,CONFIDENTIAL,NAME_SUFFIX,SEX,BIRTHDAY,PLACE_OF_BIRTH,DEATH,PLACE_OF_DEATH,REMARKS") {
		std::cerr << "error: fist line in Peoples.csv not 'ID,CONFIDENTIAL,NAME_SUFFIX,SEX,BIRTHDAY,PLACE_OF_BIRTH,DEATH,PLACE_OF_DEATH,REMARKS'\n";
		return;
	}

	while (std::getline(peoples, line)) {
		//std::cout << "line: " << line << "\n";
		auto ret = csv_parser::parse_line<
			uint64_t,
			bool,
			std::string,
			sexType,
			std::tm, std::string,
			std::tm, std::string,
			std::string>(line);

		table_peoples[std::get<0>(ret)] = std::make_tuple(
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

	//assert(false && "not implimented");
}

static void InitTitlesTable(std::ifstream& peoples) {
	assert(false && "not implimented");
}

static void InitFirstNamesTable(std::ifstream& peoples) {
	assert(false && "not implimented");
}

static void InitLastNamesTable(std::ifstream& peoples) {
	assert(false && "not implimented");
}

static void InitBloodLinesTable(std::ifstream& peoples) {
	assert(false && "not implimented");
}

static void InitRelationshipsTable(std::ifstream& peoples) {
	assert(false && "not implimented");
}

