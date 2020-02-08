#pragma once

//===== ===== Extern ===== =====
#include <vector>
#include <set>

//===== ===== Intern ===== =====
#include "../utility/types.h"

/*!
 * @brief	isolates all persons out of the list of relations
 * @return	a unique list of persons occur in the relations
 */
std::set<int> GetAllPersons(const std::set<relation>& rels);

/*!
 * @brief	isolates all persons out of the list of relations
 * @return	a unique list of persons occur in the relations
 */
std::set<int> GetAllPersons(const std::set<blood>& blds);

/*!
 * @brief	isolates all persons out of the list of relations
 * @return	a unique list of persons occur in both relations
 */
std::set<int> GetAllPersons(const std::set<blood>& blds, const std::set<relation>& rels);

/*!
 * @brief		creates a tree structure from the relations
 * @param[in] rels	the relations inside the tree
 * @return		a map of Objects with parent and children references set with the key as the person id
 */
tree CreateTree(const std::set<blood>& rels);

/*!
 * @brief						triggers the sorting process inside of the objects in the tree
 * @param[in,out] treePersons	the relational tree of peoples the has to be sorted
 */
void SortPersons(tree& treePersons);

/*!
 * @brief					converts the objects to a 2D array
 * @param[in] treePersons	a relational, and sorted tree of peoples
 * @return					a vector of vectors of person ids split into the different generations as speccifate by \p treePersons
 */
generations GenerateGenerationsFromTree(const tree& treePersons);

/*!
 * @brief					extracts all unique families from the tree
 * @param[in] treePersons	a relational tree of peoples
 * @return					a list of all unique families pressent in the relational tree of peoples
 */
std::vector<family> CreatFamilies(const tree& treePersons);

/*!
 * @brief				trys to minimice the distance between family members
 * @param[in,out] gen	the generations, that have to be sorted
 * @param[in] fam		the families, that are the base on with the algorithem tryes to minimice the distance
 */
void SortGeneration(generations& gen, const std::vector<std::vector<family>>& fams);

/*!
 * @brief				splites the families into the diferent generations (may split families into multiples between generations)
 * @param[in] families	all families
 * @param[in] peoples	the different generations
 * @return		first:	the splitted families
 * 				second:	the additional filler persons, that have to be added into
 */
std::pair<std::vector<std::vector<family>>, generations> SplitFamilysToGenerations(const std::vector<family>& families, const generations& peoples);

/*!
 * @brief						use this to get all informations needed to draw the plumming
 * @param[in] families			the families between the two generations
 * @param[in] upperGeneration	contains all "parent" persons
 * @param[in] lowerGeneration	contains all "children" persons
 * @return						all informations needet to draw the section between to generations
 */
std::vector<family> CreatePlumbingInfos(const std::vector<family>& families, const visGen& upperGeneration, const visGen& lowerGeneration);

/*!
 * @brief				serches a vector for a element
 * @param[in] target	the vector to serch in
 * @param[in] element	the element to find in \p target
 * @return				the index of \p element inside \p target vector
 * @retval -1			if \p element is not part of \p target
 */
template<typename T>
int FindInVector(const std::vector<T>& target, const T& element) {
	int size = target.size();
	for(int i = 0; i < size; i++) {
		if(target[i] == element)
			return i;
	}

	return -1;
};

/*!
 * @brief				serches a vector for a element
 * @param[in] target	the vector to serch in
 * @param[in] element	the element to find in \p target
 * @return				wether \p element is inside \p target or not
 */
template<typename T>
inline bool ExistsInVector(const std::vector<T>& target, const T& element) {
	return FindInVector(target, element) >= 0;
};

/*!
 * @brief				serches a 2DVector for a element
 * @param[in] target	the vector of vectors to be serched
 * @param[in] element	the element to be find in \p target
 * @return				wether \p element is inside \p target or not
 */
template<typename T>
bool ExistsInVector2D(const std::vector<std::vector<T>>& target, const T& element) {
	int size = target.size();
	for(int i = 0; i < size; i++) {
		int innerSize = target[i].size();
		for(int j = 0; j < innerSize; j++) {
			if(target[i][j] == element)
				return true;
		}
	}

	return false;
};
