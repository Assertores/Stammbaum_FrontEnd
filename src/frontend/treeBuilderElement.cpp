#include "treeBuilderElement.h"

#include <iostream>

void treeBuilderElement::UpdateDown(int newHight) {
	if(number < newHight) {
#ifdef DB_Tree
		std::cout << "In  (" << id << ")" << std::endl;
#endif
		number = newHight;

		for(int i = 0; i < childrens.size(); i++) {
			childrens[i]->UpdateDown(number + 1);
		}
	}
	SquashUp();//might be permanent loop
#ifdef DB_Tree
	std::cout << "Out (" << id << ")" << std::endl;
#endif
}

void treeBuilderElement::SquashUp() {
#ifdef DB_Tree
	std::cout << "Up  (" << id << ")" << std::endl;
#endif

	if(parents.size() == 0)
		return;

	//alle Parents auf den höhesten wert setzen
	int maxNumber = -1;
	for(int i = 0; i < parents.size(); i++) {
		maxNumber = maxNumber > parents[i]->number ? maxNumber : parents[i]->number;
	}

	//Childrens von Parents updaten lassen
	for(int i = 0; i < parents.size(); i++) {
		parents[i]->UpdateDown(maxNumber);
	}
}
