//===== ===== Extern ===== =====
#include <iostream>
#include <fstream>

//===== ===== Intern ===== =====
#include "utility/types.h"
#include "utility/printer.h"
#include "utility/stringCollection.h"
#include "backend/dataHandler.h"
#include "frontend/calculate.h"
#include "frontend/MLMSElement.h"

void InputQuary(int* id, int* dist);

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

		auto relations = dataHandler::GetRelations(id, dist);//call to Interface
		auto smalTree = CreateTree(relations.first);
		auto generations = SortPersons(smalTree);
		auto families = CreatFamilies(smalTree);

		std::vector<visGen> treePeopleVisualisator;
		for(int i = 0; i < generations.size(); i++) {
			visGen element;
			for(auto& it : generations[i]) {
				element.push_back(std::pair(it, MLMSElement(PersonToString(dataHandler::GetPerson(it), false), Box)));//call to Interface
			}
			treePeopleVisualisator.push_back(element);
		}


		auto generationFamilys = SplitFamilysToGenerations(families, generations);
		for(int i = 0; i < generationFamilys.second.size(); i++) {
			for(auto& it : generationFamilys.second[i]) {
				treePeopleVisualisator[i].push_back(std::pair<int, MLMSElement>(it, MLMSElement("", NoBox, '|', 1)));
			}
		}

		std::vector<std::vector<family>> generationPlummbings;
		for(int i = 0; i < generationFamilys.first.size(); i++) {
			generationPlummbings.push_back(CreatePlumbingInfos(generationFamilys.first[i], treePeopleVisualisator[i], treePeopleVisualisator[i + 1]));
		}
		generationPlummbings.push_back(std::vector<family>());

		//----- ----- rendering ----- -----

		for(int g = 0; g < treePeopleVisualisator.size(); g++) {
			int maxLineCount = 0;
			for(int i = 0; i < treePeopleVisualisator[g].size(); i++) {
				int newLineCount = treePeopleVisualisator[g][i].second.GetLineCount();
				maxLineCount = maxLineCount > newLineCount ? maxLineCount : newLineCount;
			}
			for(int j = 0; j < maxLineCount; j++) {
				for(int i = 0; i < treePeopleVisualisator[g].size(); i++) {
					std::cout << treePeopleVisualisator[g][i].second.GetLine(j);
				}
				std::cout << std::endl;
			}
			std::cout << PlumbGeneration(generationPlummbings[g]) << std::endl;
		}
	}

	//===== ===== Clean Up ===== =====

	peoples.close();
	titles.close();
	firstNames.close();
	lastNames.close();
	bloodLines.close();
	relationships.close();

	return 0;
}

void InputQuary(int* id, int* dist) {

	std::cout << INPUTREQUEST;
	std::cin >> *id >> *dist;

	while(std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore();
		std::cin.ignore(INT_MAX, '\n');

		std::cout << FAILEDINPUT;
		std::cin >> *id >> *dist;
	}
}
