#pragma once

//===== ===== Extern ===== =====
#include <vector>

//===== ===== Intern ===== =====
#include "../utility/types.h"

class treeBuilderElement{
public:
	void UpdateDown(int newHight);
	void SquashUp();

	int number = -1;

	std::vector<treeBuilderElement*> parents;
	std::vector<treeBuilderElement*> childrens;
};