#pragma once

//===== ===== Extern ===== =====
#include <vector>
#include <set>

//===== ===== Intern ===== =====
#include "../utility/types.h"

std::set<int> GetAllPersons(const std::set<relation>& rels);

std::set<int> GetAllPersons(const std::set<blood>& blds);

std::set<int> GetAllPersons(const std::set<blood>& blds, const std::set<relation>& rels);

tree CreateTree(const std::set<blood>& rels);

void SortPersons(tree& treePersons);

generations GenerateGenerationsFromTree(const tree& treePersons);

std::vector<family> CreatFamilies(const tree& treePersons);

void SortGeneration(generations& gen, const std::vector<family>& fam);

std::pair<std::vector<std::vector<family>>, generations> SplitFamilysToGenerations(const std::vector<family>& families, const generations& peoples);

std::vector<family> CreatePlumbingInfos(const std::vector<family>& families, const visGen& upperGeneration, const visGen& lowerGeneration);

template<typename T>
int FindInVector(const std::vector<T>& target, const T& element) {
	int size = target.size();
	for(int i = 0; i < size; i++) {
		if(target[i] == element)
			return i;
	}

	return -1;
}
