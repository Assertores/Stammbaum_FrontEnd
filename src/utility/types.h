#pragma once

//===== ===== Extern ===== =====
#include <vector>
#include <chrono>
#include <map>
#include <set>

//===== ===== Intern ===== =====
#include "../frontend/treeBuilderElement.h"
#include "../frontend/MLMSElement.h"

typedef const char* cString;
typedef std::map<int, treeBuilderElement> tree;
typedef std::vector<std::set<int>> generations;
typedef std::pair<std::set<int>, std::set<int>> family;
typedef std::vector<std::pair<int, MLMSElement>> visGen;//visual Generation

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
	std::vector<std::string> titles;
	std::vector<std::string> firstNames;
	std::string suffix;
	std::vector<std::string> lastNames;

	sexType sex;

	std::tm birthday;
	std::string placeOfBirth;

	std::tm death;
	std::string placeOfDeath;

	std::string remarks;

	//audiofile
	//pictures
	//video
};

