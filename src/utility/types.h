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
	Male,
	Female,
	Deverce,
};

struct blood {
	int objectID;
	int subjectID;
	relType type;

	bool operator < (const blood& rhs) const {
		return (objectID != rhs.objectID) ? objectID < rhs.objectID : subjectID < rhs.subjectID;
	}
};

struct relation {
	int objectID;
	int subjectID;
	relType type;
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	bool operator < (const blood& rhs) const {
		return (objectID != rhs.objectID) ? objectID < rhs.objectID : subjectID < rhs.subjectID;
	}
};

struct personInfos {
	std::vector<cString> titles;
	std::vector<cString> firstNames;
	cString suffix = nullptr;
	std::vector<cString> lastNames;
	sexType sex;
	std::chrono::system_clock::time_point birthday;
	cString placeOfBirth = nullptr;
	std::chrono::system_clock::time_point death;
	cString placeOfDeath = nullptr;
	cString remarks = nullptr;
	//audiofile
	//pictures
	//video
};