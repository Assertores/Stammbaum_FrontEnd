#include <iostream>
#include <vector>
#include <chrono>
#include <set>

#include "utility/types.h"
#include "utility/printer.h"
#include "frontend/calculate.h"
#include "frontend/MLMSElement.h"

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

	p1.birthday = std::chrono::system_clock::now();
	p1.placeOfBirth = "Burgkrichen";

	p1.death = std::chrono::system_clock::now();
	p1.placeOfDeath = "Berlin";

	p1.remarks = "is testing stuff";

	std::cout << PersonToString(p1) << std::endl << std::endl;
	std::cout << PersonToString(p1, false) << std::endl << std::endl;

	MLMSElement p1Handler(PersonToString(p1, false), Box);
	MLMSElement p1Long(PersonToString(p1), Box);

	std::cout << "element width: " << p1Handler.GetSize() << ", " << p1Long.GetSize() << std::endl;
	for(int i = 0; i < p1Long.GetLineCount(); i++) {
		std::cout << p1Handler.GetLine(i) << " ! " << p1Long.GetLine(i) << std::endl;
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
	
	auto retVal = SortPersons(relations);
	
	for(int i = 0; i < retVal.size(); i++) {
		for(auto& it : retVal[i]) {
			std::cout << it << ", ";
		}std::cout << std::endl;
	}

	return 0;
}
