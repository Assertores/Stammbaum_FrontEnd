#include <iostream>
#include <vector>
#include <chrono>
#include <set>

#include "utility/types.h"
#include "utility/printer.h"
#include "frontend/calculate.h"
#include "frontend/MLMSElement.h"
#include <csv_parser.hpp>

int main(void) {

	//===== ===== Test Persons ===== =====

	personInfos p1;

	p1.titles.push_back("Prof.");
	p1.titles.push_back("Dr.");
	p1.titles.push_back("Dr.");

	p1.firstNames.push_back("Andreas");
	p1.firstNames.push_back("Erik");
	p1.firstNames.push_back("Franz");

	p1.suffix = "von und zu";

	p1.lastNames.push_back("Hartl");
	p1.lastNames.push_back("Mueller");
	p1.lastNames.push_back("Edmeier");

	p1.sex = Male;

	//p1.birthday = std::chrono::system_clock::now();
	p1.birthday = csv_parser::parse_entry<std::tm>("04.05.1996");
	p1.placeOfBirth = "Burgkrichen";

	//p1.death = std::chrono::system_clock::now();
	p1.death = csv_parser::parse_entry<std::tm>("11.11.2020");
	p1.placeOfDeath = "Berlin";

	p1.remarks = "is testing stuff";

	std::cout << PersonToString(p1) << std::endl << std::endl;
	std::cout << PersonToString(p1, false) << std::endl << std::endl;

	MLMSElement pHolder[3] = {
		MLMSElement(PersonToString(p1, false), Box),
		MLMSElement("", NoBox , '|', 1),
		MLMSElement(PersonToString(p1), Box),
	};

	int maxLength = -1;
	for(int i = 0; i < 3; i++) {
		maxLength = maxLength > pHolder[i].GetLineCount() ? maxLength : pHolder[i].GetLineCount();
	}

	for(int i = 0; i < maxLength; i++) {
		for(int j = 0; j < 3; j++) {
			std::cout << pHolder[j].GetLine(i);
		}std::cout << std::endl;
	}

	personInfos p2;

	std::cout << PersonToString(p2) << std::endl << std::endl;
	std::cout << PersonToString(p2, false) << std::endl << std::endl;

	//===== ===== Relations ===== =====

	std::set<blood> relations;

	relations.emplace(blood {0, 11, Father});
	relations.emplace(blood {1, 11, Mother});
	relations.emplace(blood {0, 2, Father});
	relations.emplace(blood {1, 2, Mother});
	relations.emplace(blood {0, 4, Father});
	relations.emplace(blood {1, 4, Mother});
	relations.emplace(blood {2, 9, Father});
	relations.emplace(blood {3, 9, Mother});
	relations.emplace(blood {4, 6, Father});
	relations.emplace(blood {5, 6, Mother});
	relations.emplace(blood {7, 8, Father});
	relations.emplace(blood {6, 8, Mother});
	relations.emplace(blood {9, 10, Father});
	relations.emplace(blood {8, 10, Mother});
	relations.emplace(blood {12, 13, Father});
	relations.emplace(blood {11, 13, Mother});
	relations.emplace(blood {14, 15, Father});
	relations.emplace(blood {13, 15, Mother});
	relations.emplace(blood {11, 16, Mother});
	relations.emplace(blood {10, 16, Father});
	relations.emplace(blood {15, 17, Father});
	relations.emplace(blood {16, 17, Mother});

	auto tree = CreateTree(relations);
	auto retVal = SortPersons(tree);

	for(int i = 0; i < retVal.size(); i++) {
		for(auto& it : retVal[i]) {
			std::cout << it << ", ";
		}std::cout << std::endl;
	}
	std::cout << std::endl;

	auto retVal2 = CreatFamilies(tree);

	for(int i = 0; i < retVal2.size(); i++) {
		std::cout << "[";
		for(auto& it : retVal2[i].first) {
			std::cout << it << ", ";
		}
		std::cout << "][";
		for(auto& it : retVal2[i].second) {
			std::cout << it << ", ";
		}
		std::cout << "]" << std::endl;
	}

	std::cout << std::endl;

	std::vector<std::pair<std::set<int>, std::set<int>>> plumbing;
	
	{
		std::pair<std::set<int>, std::set<int>> element;

		element.first.emplace(4);
		element.first.emplace(18);

		element.second.emplace(12);

		plumbing.push_back(element);
	}
	
	{
		std::pair<std::set<int>, std::set<int>> element;

		element.first.emplace(8);

		element.second.emplace(7);

		plumbing.push_back(element);
	}
	
	{
		std::pair<std::set<int>, std::set<int>> element;

		element.first.emplace(11);
		element.first.emplace(24);

		element.second.emplace(3);

		plumbing.push_back(element);
	}
	
	MLMSElement topElements[5] {
		MLMSElement("0", Box, ' ', 5),
		MLMSElement("", NoBox , '|', 1),
		MLMSElement("2", Box, ' ', 3),
		MLMSElement("3", Box, ' ', 7),
		MLMSElement("4", Box, ' ', 2),
	};

	MLMSElement bottomElements[3] {
		MLMSElement("5", Box, ' ', 4),
		MLMSElement("", NoBox , '|', 1),
		MLMSElement("7", Box, ' ', 7),
	};

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 5; j++) {
			std::cout << topElements[j].GetLine(i);
		}std::cout << std::endl;
	}
	std::cout << PlumbGeneration(plumbing) << std::endl;
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			std::cout << bottomElements[j].GetLine(i);
		}std::cout << std::endl;
	}

	return 0;
}
