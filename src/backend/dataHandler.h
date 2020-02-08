#pragma once

//===== ===== Extern ===== =====
#include <fstream>
#include <set>

//===== ===== Intern ===== =====
#include "../utility/types.h"


namespace dataHandler {
	/*!
	 * @brief	initialices all tables at once.
	 * @pre		all table files are opend
	 * @param peoples, titles, firstNames, lastNames, bloodLines, relationships	read file streams to the assosiated table
	 */
	void InitTables(std::ifstream& peoples, std::ifstream& titles, std::ifstream& firstNames, std::ifstream& lastNames, std::ifstream& bloodLines, std::ifstream& relationships);

	/*!
	 * @brief			retreave a subtree of the data. retreaves the whole tree or even multiple trees.
	 * @param rootID	the id of the person in question
	 * @param dinst		the max distance of relationships removed from the person
	 * @return			a list of all relevant relations
	 */
	std::pair<std::set<blood>, std::set<relation>> GetRelations(const int rootID = 0, const int dinst = -1);

	/*!
	 * @brief	you know. SQL and so ...
	 * @return	all relevant informations of an specific person
	 */
	personInfos GetPerson(const int personID);

	
} //dataHandler

