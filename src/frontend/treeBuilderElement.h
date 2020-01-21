#pragma once

//===== ===== Extern ===== =====
#include <vector>

//===== ===== Intern ===== =====

class treeBuilderElement{
public:
	void UpdateDown(int newHight, bool fromChild = false);
	void SquashUp();

	int number = -1;
	int id;

	std::vector<treeBuilderElement*> parents;
	std::vector<treeBuilderElement*> childrens;
};