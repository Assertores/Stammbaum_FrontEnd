//===== ===== Extern ===== =====
#include <cassert>

//===== ===== Intern ===== =====
#include "dataHandler.h"

void dataHandler::InitTables(const std::ifstream& peoples, const std::ifstream& titles, const std::ifstream& firstNames, const std::ifstream& lastNames, const std::ifstream& bloodLines, const std::ifstream& relationships) {
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

std::set<blood> dataHandler::GetBloodLines(const int rootID = 0, const int dinst = -1){
	assert(false && "not implimented");
}

std::set<relation> dataHandler::GetRelations(const int rootID, const int dinst){
	assert(false && "not implimented");
}

personInfos dataHandler::GetPerson(const int personID){
	assert(false && "not implimented");
}

void dataHandler::InitPeoplesTable(const std::ifstream& peoples){
	assert(false && "not implimented");
}

void dataHandler::InitTitlesTable(const std::ifstream& peoples){
	assert(false && "not implimented");
}

void dataHandler::InitFirstNamesTable(const std::ifstream& peoples){
	assert(false && "not implimented");
}

void dataHandler::InitLastNamesTable(const std::ifstream& peoples){
	assert(false && "not implimented");
}

void dataHandler::InitBloodLinesTable(const std::ifstream& peoples){
	assert(false && "not implimented");
}

void dataHandler::InitRelationshipsTable(const std::ifstream& peoples){
	assert(false && "not implimented");
}
