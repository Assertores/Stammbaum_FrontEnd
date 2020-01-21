#include "treeBuilderElement.h"

#include <iostream>

void treeBuilderElement::UpdateDown(int newHight, bool fromChild/* = false*/) {
#ifdef DB_TREE
		std::cout << "In  (" << id << "| " << number << ", " << newHight << ")" << std::endl;
#endif
	if(number < newHight) {
		number = newHight;

		for(size_t i = 0; i < childrens.size(); i++) {
			childrens[i]->UpdateDown(number + 1);
		}
	}
	if(!fromChild)
		SquashUp();//might be permanent loop
#ifdef DB_TREE
	std::cout << "Out (" << id << "| " << number << ")" << std::endl;
#endif
}

void treeBuilderElement::SquashUp() {
	if(parents.size() == 0)
		return;

	//alle Parents auf den höhesten wert setzen
	int maxNumber = -1;
	for(size_t i = 0; i < parents.size(); i++) {
		maxNumber = maxNumber > parents[i]->number ? maxNumber : parents[i]->number;
	}
#ifdef DB_TREE
	std::cout << "Up  (" << id << "| " << maxNumber << ")" << std::endl;
#endif

	//Childrens von Parents updaten lassen
	for(size_t i = 0; i < parents.size(); i++) {
		parents[i]->UpdateDown(maxNumber, true);
	}
}

