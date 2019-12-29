//===== ===== Extern ===== =====
#include <iostream>
#include <fstream>
#include <string>
#include <set>

//===== ===== Intern ===== =====
#include "utility/types.h"
#include "utility/stringCollection.h"
#include "backend/dataHandler.h"

void InputQuary(int* id, int* dist);
std::vector<std::set<int>>SortPersons(std::set<blood>& rels);

int main(int argc, cString argv[]) {

	//===== ===== Init ===== =====

	if(2 != argc) {
		std::cout << ERROR_ARGUMENTCOUNT << std::endl;
		return -1;
	}

	std::string path = argv[1];

	std::ifstream peoples(path + FILE_PEOPLES);

	if(!peoples) {
		std::cout << ERROR_PEOPLES << std::endl;
		return -2;
	}

	std::ifstream titles(path + FILE_TITLES);

	if(!titles) {
		std::cout << ERROR_TITLES << std::endl;
		return -3;
	}

	std::ifstream firstNames(path + FILE_FIRSTNAMES);

	if(!firstNames) {
		std::cout << ERROR_FIRSTNAMES << std::endl;
		return -4;
	}

	std::ifstream lastNames(path + FILE_LASTNAMES);

	if(!lastNames) {
		std::cout << ERROR_LASTNAMES << std::endl;
		return -5;
	}

	std::ifstream bloodLines(path + FILE_BLOODLINES);

	if(!bloodLines) {
		std::cout << ERROR_BLOODLINES << std::endl;
		return -6;
	}

	std::ifstream relationships(path + FILE_RELATIONSHIPS);

	if(!relationships) {
		std::cout << ERROR_RELATIONSHIPS << std::endl;
		return -7;
	}

	dataHandler::InitTables(peoples, titles, firstNames, lastNames, bloodLines, relationships);

	//===== ===== Programm Loop ===== =====

	int id;
	int dist;

	bool exit = false;
	while(!exit) {
		//----- ----- input ----- -----
		InputQuary(&id, &dist);

		//----- ----- logic ----- -----
		auto bloods = dataHandler::GetBloodLines(id, dist);
		auto rels = dataHandler::GetRelations(id, dist);



		//----- ----- rendering ----- -----

	}

	peoples.close();
	titles.close();
	firstNames.close();
	lastNames.close();
	bloodLines.close();
	relationships.close();

	return 0;
}

void InputQuary(int* id, int* dist){
	
	std::cout << INPUTREQUEST;
	std::cin >> *id >> *dist;

	while(std::cin.fail()){
		std::cin.clear();
		std::cin.ignore();
		std::cin.ignore(INT_MAX, '\n');

		std::cout << FAILEDINPUT;
		std::cin >> *id >> *dist;
	}
}

std::vector<std::set<int>>SortPersons(std::set<blood>& rels){
	std::vector<std::set<int>> value;
	std::set<int> highestPersons;
	
	for(int i = 0; i < rels.size; i++){
		bool isHighest = true;
		for(int j = 0; j < rels.size; j++){
			if(rels[i].objectID == rels[j].subjectID){//person has parents
				isHighest = false;
				break;
			}
		}

		if(isHighest){
			highestPersons.emplace(rels[i].subjectID);
		}
	}

	value.emplace_back(highestPersons);

}
