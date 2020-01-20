#include "calculate.h"

#include <map>

#include "treeBuilderElement.h"

std::set<int> GetAllPersons(std::set<relation>& rels) {
	std::set<int> value;

	for(auto& it : rels) {
		value.emplace(it.objectID);
		value.emplace(it.subjectID);
	}

	return value;
}

std::set<int> GetAllPersons(std::set<blood>& blds) {
	std::set<int> value;

	for(auto& it : blds) {
		value.emplace(it.objectID);
		value.emplace(it.subjectID);
	}

	return value;
}

std::set<int> GetAllPersons(std::set<blood>& blds, std::set<relation>& rels) {
	std::set<int> value;

	value = GetAllPersons(blds);
	auto tmp = GetAllPersons(rels);
	value.insert(tmp.begin(), tmp.end());

	return value;
}

std::vector<std::set<int>>SortPersons(std::set<blood>& rels) {
	std::vector<std::set<int>> value;
	std::map<int, treeBuilderElement> treePersons;

	{
		std::set<int> allPersons = GetAllPersons(rels);
		for(auto& it : allPersons) {
			treeBuilderElement element;
			element.id = it;
			treePersons[it] = element;
		}
	}

	for(auto& it : rels) {
		treePersons[it.objectID].childrens.push_back(&treePersons[it.subjectID]);
		treePersons[it.subjectID].parents.push_back(&treePersons[it.objectID]);
	}

	for(auto& it : treePersons) {
		if(it.second.parents.size() <= 0)
			it.second.UpdateDown(0);
	}

	{
		int max = -1;
		for(auto& it : treePersons) {
			max = max > it.second.number ? max : it.second.number;
		}

		for(int i = 0; i < max + 1; i++) {
			value.push_back(std::set<int>());
		}
	}

	for(auto& it : treePersons) {
		value[it.second.number].emplace(it.first);
	}

	return value;
}