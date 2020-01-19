#include "treeBuilderElement.h"

void treeBuilderElement::UpdateDown(int parentHight) {
	number = number > parentHight ? number : parentHight + 1;

	for(int i = 0; i < childrens.size; i++) {
		childrens[i].UpdateDown(number);
	}
}

void treeBuilderElement::SquashUp() {
	int tmp = -1;

	if(parents.size > 0) {
		
	}
	else {
	}
}