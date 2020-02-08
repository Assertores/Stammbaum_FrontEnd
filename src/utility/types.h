#pragma once

//===== ===== Extern ===== =====
#include <vector>
#include <chrono>
#include <map>
#include <set>

//===== ===== Intern ===== =====
#include "../frontend/treeBuilderElement.h"
#include "../frontend/MLMSElement.h"

typedef const char* cString;								//!< @typedef c-style strings
typedef std::map<int, treeBuilderElement> tree;				//!< @typedef relational tree
typedef std::vector<std::vector<int>> generations;			//!< @typedef 2DArray of personIDs
typedef std::pair<std::set<int>, std::set<int>> family;		//!< @typedef set of parentIDs and set of ChildrenIDs
typedef std::vector<std::pair<int, MLMSElement>> visGen;	//!< @typedef visual Generation containing all informations to draw a generation

/*! relation Type */
enum relType {
	Father,
	Mother,
	FosterMother,
	Married,
};

/*! sex Type */
enum sexType {
	Male,
	Female,
	Deverce,
};

/*! relations by bloud that will be translated in parent-children relations */
struct blood {
	int objectID;	//!< parent
	int subjectID;	//!< child
	relType type;	//!< \p objectID is \p type of \p subjectID

	/*! needed for map */
	bool operator < (const blood& rhs) const {
		return (objectID != rhs.objectID) ? objectID < rhs.objectID : subjectID < rhs.subjectID;
	}
};

/*! artefitial relations between to people e.g. married, friend */
struct relation {
	int objectID;
	int subjectID;
	relType type;
	std::tm start;	//!< start time of the relation
	std::tm end;	//!< end time of the relation (divorce, etc.)

	/*! needed for map */
	bool operator < (const blood& rhs) const {
		return (objectID != rhs.objectID) ? objectID < rhs.objectID : subjectID < rhs.subjectID;
	}
};

/*!
 * all informations regarding to a person
 */
struct personInfos {
	std::vector<std::string> titles;		//!< all titles (Dr., Prof., etc.)
	std::vector<std::string> firstNames;	//!< all first names
	std::string suffix;						//!< e.g. von und zu
	std::vector<std::string> lastNames;		//!< all last names e.g. from previos mareys

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

