#pragma once

//===== ===== Extern ===== =====
#include <fstream>
#include <set>

//===== ===== Intern ===== =====
#include "../utility/types.h"


static class dataHandler{
public:
	/// <summary>
	/// initialices all tables at once. asserts all table files are opend
	/// </summary>
	static void InitTables(const std::ifstream& peoples, const std::ifstream& titles, const std::ifstream& firstNames, const std::ifstream& lastNames, const std::ifstream&bloodLines, const std::ifstream& relationships);

	/// <summary>
	/// retreave a subtree of the data. retreaves the whole tree or even multiple trees. only bloodlines
	/// </summary>
	/// <param rootID = 0>the id of the person in question</param>
	/// <param dinst = -1>the max distance of relationships removed from the person</param>
	/// <return>a list of all relevant relations</return>
	static std::set<blood> GetBloodLines(const int rootID = 0, const int dinst = -1);

	/// <summary>
	/// retreave a subtree of the data. retreaves the whole tree or even multiple trees. only relationships
	/// </summary>
	/// <param rootID = 0>the id of the person in question</param>
	/// <param dinst = -1>the max distance of relationships removed from the person</param>
	/// <return>a list of all relevant relations</return>
	static std::set<relation> GetRelations(const int rootID = 0, const int dinst = -1);

	/// <summary>
	/// you know. SQL and so ...
	/// </summary>
	/// <return>all relevant informations of an specific person</return>
	static personInfos GetPerson(const int personID);

private:

	static void InitPeoplesTable(const std::ifstream& peoples);
	static void InitTitlesTable(const std::ifstream& peoples);
	static void InitFirstNamesTable(const std::ifstream& peoples);
	static void InitLastNamesTable(const std::ifstream& peoples);
	static void InitBloodLinesTable(const std::ifstream& peoples);
	static void InitRelationshipsTable(const std::ifstream& peoples);
};