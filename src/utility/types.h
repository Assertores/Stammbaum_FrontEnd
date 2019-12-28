#pragma once

//===== ===== Extern ===== =====
#include <vector>
#include <chrono>

//===== ===== Intern ===== =====

typedef char* cString;

enum relType {
	Father,
	Mother,
	FosterMother,
	Married,
};

enum sexType {
	male,
	female,
	deverce,
};

struct relation {
	int objectID;
	int subjectID;
	relType type;
};

struct personInfos{
	std::vector<cString> titles;
	std::vector<cString> firstNames;
	cString suffix;
	std::vector<cString> lastNames;
	sexType sex;
	std::chrono::system_clock::time_point birthday;
	cString placeOfBirth;
	std::chrono::system_clock::time_point death;
	cString placeOfDeath;
	cString remarks;
	//audiofile
	//pictures
	//video
};