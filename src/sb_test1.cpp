#include <iostream>
#include <vector>
#include <chrono>

#include "utility/types.h"
#include "utility/printer.h"

int main(void) {

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

	p1.birthday = std::chrono::system_clock::now();
	p1.placeOfBirth = "Burgkrichen";

	p1.death = std::chrono::system_clock::now();
	p1.placeOfDeath = "Berlin";

	p1.remarks = "is testing stuff";

	std::cout << PersonToString(p1) << std::endl << std::endl;
	std::cout << PersonToString(p1, false) << std::endl << std::endl;

	personInfos p2;

	std::cout << PersonToString(p2) << std::endl << std::endl;
	std::cout << PersonToString(p2, false) << std::endl << std::endl;


	return 0;
}

