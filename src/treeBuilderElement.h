#pragma once

//===== ===== Extern ===== =====
#include <vector>

//===== ===== Intern ===== =====
#include "utility/types.h"

class treeBuilderElement{
public:
	void UpdateDown(int parentHight);
	void SquashUp();

	int number = 0;

	std::vector<treeBuilderElement> parents;
	std::vector<treeBuilderElement> childrens;
};