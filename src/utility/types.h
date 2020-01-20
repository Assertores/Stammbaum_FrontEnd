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
	std::tm start;
	std::tm end;

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
	std::tm birthday;
	cString placeOfBirth = nullptr;
	std::tm death;
	cString placeOfDeath = nullptr;
	cString remarks = nullptr;
	//audiofile
	//pictures
	//video
};