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

void ExecuteTree(std::vector<std::string>& input);
void ExecutePerson(std::vector<std::string>& input);

int main(int argc, cString argv[]) {
	//===== ===== Init ===== =====
	std::string path;

	if(2 <= argc) {
		path = argv[1];
	} else{
		std::cout << ERROR_ARGUMENTCOUNT << ". Please input the path to the database: ";

		if(std::cin.eof()) {
			return -1;
		}

		std::getline(std::cin, path);
		if(path.empty())
			return -1;
	}

	

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

	bool exit = false;
	std::string inputBuffer;
	std::vector<std::string> input;

	while(!exit) {
		//----- ----- input ----- -----
		input.clear();

		// eg CTRL-D in bash
		if (std::cin.eof()) {
			exit = true;
			std::cout << '\n';
			break;
		}

		std::cout << "> ";

		std::getline(std::cin, inputBuffer);
		if (inputBuffer.empty())
			continue;

		std::istringstream tmp(inputBuffer);
		while(tmp.good()) {
			inputBuffer.clear();
			tmp >> inputBuffer;
			input.push_back(inputBuffer);
		}

#ifdef _WIN32
		system("cls");
#else
		system("clear");
#endif

		//----- ----- Logic and Rendering ----- -----

		if(input.size() <= 0) {
			std::cout << HELP_HELP << std::endl;
			continue;
		}
		if(input[0] == COMMAND_EXIT ||
		   input[0] == COMMAND_SEXIT ||
		   input[0] == COMMAND_QUIT ||
		   input[0] == COMMAND_SQUIT) {
			exit = true;
		} else if(input[0] == COMMAND_HELP ||
				  input[0] == COMMAND_SHELP) {
			if(input.size() <= 1) {
				std::cout << HELP_HELP << std::endl;
			} else if(input[1] == COMMAND_EXIT ||
					  input[1] == COMMAND_SEXIT ||
					  input[1] == COMMAND_QUIT ||
					  input[1] == COMMAND_SQUIT) {
				std::cout << HELP_QUIT << std::endl;
			} else if(input[1] == COMMAND_TREE) {
				std::cout << HELP_TREE << std::endl;
			} else if(input[1] == COMMAND_PERSON) {
				std::cout << HELP_PERSON << std::endl;
			} else {
				std::cout << HELP_HELP << std::endl;
			}
		
		} else if(input[0] == COMMAND_TREE) {
			ExecuteTree(input);
		} else if(input[0] == COMMAND_PERSON) {
			ExecutePerson(input);
		} else {
			std::cout << COM_NOT_FOUND << std::endl;
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

void ExecuteTree(std::vector<std::string>& input) {
	if(input.size() < 3) {
		std::cout << NOT_ENOUGH_PARAMETER << std::endl;
		return;
	}

	//----- ----- input ----- -----

	int id;
	int dist;

	id = atoi(input[1].c_str());
	dist = atoi(input[2].c_str());

	//----- ----- logic ----- -----

	auto relations = dataHandler::GetRelations(id, dist);//call to API
	auto smalTree = CreateTree(relations.first);
	SortPersons(smalTree);
	auto generations = GenerateGenerationsFromTree(smalTree);
	auto families = CreatFamilies(smalTree);
	SortGeneration(generations, families);

	std::vector<visGen> treePersonVisualisator;
	for(int i = 0; i < generations.size(); i++) {
		visGen element;
		for(auto& it : generations[i]) {
			element.push_back(std::pair(it, MLMSElement(PersonToString(dataHandler::GetPerson(it), false), Box)));//call to API
		}
		treePersonVisualisator.push_back(element);
	}


	auto generationFamilys = SplitFamilysToGenerations(families, generations);
	for(int i = 0; i < generationFamilys.second.size(); i++) {
		for(auto& it : generationFamilys.second[i]) {
			treePersonVisualisator[i].push_back(std::pair<int, MLMSElement>(it, MLMSElement("", NoBox, '|', 1)));
		}
	}

	std::vector<std::vector<family>> generationPlummbings;
	for(int i = 0; i < generationFamilys.first.size(); i++) {
		generationPlummbings.push_back(CreatePlumbingInfos(generationFamilys.first[i], treePersonVisualisator[i], treePersonVisualisator[i + 1]));
	}
	generationPlummbings.push_back(std::vector<family>());

	//----- ----- rendering ----- -----

	for(int g = 0; g < treePersonVisualisator.size(); g++) {
		int maxLineCount = 0;
		for(int i = 0; i < treePersonVisualisator[g].size(); i++) {
			int newLineCount = treePersonVisualisator[g][i].second.GetLineCount();
			maxLineCount = maxLineCount > newLineCount ? maxLineCount : newLineCount;
		}
		for(int j = 0; j < maxLineCount; j++) {
			for(int i = 0; i < treePersonVisualisator[g].size(); i++) {
				std::cout << treePersonVisualisator[g][i].second.GetLine(j);
			}
			std::cout << std::endl;
		}
		std::cout << PlumbGeneration(generationPlummbings[g]) << std::endl;
	}
}

void ExecutePerson(std::vector<std::string>& input) {
	if(input.size() < 2) {
		std::cout << NOT_ENOUGH_PARAMETER << std::endl;
		return;
	}

	//----- ----- input ----- -----

	int id = stoi(input[1]);

	//----- ----- logic ----- -----

	personInfos person = dataHandler::GetPerson(id);//call to API

	//----- ----- rendering ----- -----

	std::cout << PersonToString(person) << std::endl;
}
