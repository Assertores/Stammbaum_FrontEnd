//===== ===== Extern ===== =====
#include <cassert>

//===== ===== Intern ===== =====
#include "dataHandler.h"

#include <csv_parser.hpp>
#include "../utility/types_parser.hpp"

/// <summary>
/// Table types
/// int, bool, string, sexType, tm, string, tm, string, string
/// </summary>
void InitPeoplesTable(const std::ifstream& peoples);

/// <summary>
/// Table types
/// int, int, bool, string
/// </summary>
void InitTitlesTable(const std::ifstream& peoples);

/// <summary>
/// Table types
/// int, int, bool, string
/// </summary>
void InitFirstNamesTable(const std::ifstream& peoples);

/// <summary>
/// Table types
/// int, int, bool, string
/// </summary>
void InitLastNamesTable(const std::ifstream& peoples);

/// <summary>
/// Table types
/// int, int, bool, relType
/// </summary>
void InitBloodLinesTable(const std::ifstream& peoples);

/// <summary>
/// Table types
/// int, int, bool, relType, tm, tm
/// </summary>
void InitRelationshipsTable(const std::ifstream& peoples);

namespace dataHandler {
	void InitTables(const std::ifstream& peoples, const std::ifstream& titles, const std::ifstream& firstNames, const std::ifstream& lastNames, const std::ifstream& bloodLines, const std::ifstream& relationships) {
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

void InitPeoplesTable(const std::ifstream& peoples) {
	assert(false && "not implimented");
}

void InitTitlesTable(const std::ifstream& peoples) {
	assert(false && "not implimented");
}

void InitFirstNamesTable(const std::ifstream& peoples) {
	assert(false && "not implimented");
}

void InitLastNamesTable(const std::ifstream& peoples) {
	assert(false && "not implimented");
}

void InitBloodLinesTable(const std::ifstream& peoples) {
	assert(false && "not implimented");
}

void InitRelationshipsTable(const std::ifstream& peoples) {
	assert(false && "not implimented");
}
