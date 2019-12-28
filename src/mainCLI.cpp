//===== ===== Extern ===== =====
#include <iostream>
#include <fstream>
#include <string>

//===== ===== Intern ===== =====
#include "utility/types.h"

int main (int argc, cString argv[]){

	if(2 != argc){
		std::cout << "you have to pass exagtly one argument" << std::endl;
		return -1;
	}

	std::string path = argv[1];

	std::ifstream peoples(path + "/People.csv");

	if(!peoples){
		std::cout << "no People.csv file found" << std::endl;
		return -2;
	}

	std::ifstream titles(path + "/Titles.csv");

	if(!titles) {
		std::cout << "no Titles.csv file found" << std::endl;
		return -3;
	}

	std::ifstream firstNames(path + "/FirstNames.csv");

	if(!firstNames) {
		std::cout << "no FirstNames.csv file found" << std::endl;
		return -4;
	}

	std::ifstream lastNames(path + "/LastNames.csv");

	if(!lastNames) {
		std::cout << "no LastNames.csv file found" << std::endl;
		return -5;
	}


	std::ifstream bloodLines(path + "/Bloodline.csv");

	if(!bloodLines) {
		std::cout << "no Bloodline.csv file found" << std::endl;
		return -6;
	}

	std::ifstream relationships(path + "/Relationships.csv");

	if(!relationships) {
		std::cout << "no Relationships.csv file found" << std::endl;
		return -7;
	}

	//funktion call to backend

	//
	
	peoples.close();
	titles.close();
	firstNames.close();
	lastNames.close();
	bloodLines.close();
	relationships.close();

	return 0;
}
