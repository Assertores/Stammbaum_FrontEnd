#pragma once

//===== ===== Extern ===== =====
#include <vector>

//===== ===== Intern ===== =====

/*!
 * dummy element to build the tree from the relations
 */
class treeBuilderElement{
public:
	/*!
	 * @brief			positions all childrens downwards recursive to new hight
	 * @param newHight	the hight of the object
	 * @param fromChild	wheter the function call comes from a child or a parrent.
	 *					if false it will automaticly call SquashUp
	 */
	void UpdateDown(int newHight, bool fromChild = false);

	/*!
	 * @brief	alines all parents to the lowest one
	 * @remarks	will call \link treeBuilderElement::UpdateDown() \endlink for all parents
	 */
	void SquashUp(void);

	int number = -1;	//!< the "generation" it is in
	int id;				//!< debug infos the id of the person

	std::vector<treeBuilderElement*> parents;	//!< pointers to all parents
	std::vector<treeBuilderElement*> childrens;	//!< pointers to all childrens
};