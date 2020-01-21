#include "calculate.h"

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
	value.merge(GetAllPersons(rels));

	return value;
}

tree CreateTree(std::set<blood>& rels) {
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

	return treePersons;
}

peoples SortPersons(tree& treePersons) {
	peoples value;


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

std::vector<family> CreatFamilies(tree& treePersons) {
	std::vector<family> value;

	std::set<int> childrenToCheck;
	for(auto& it : treePersons) {
		childrenToCheck.emplace(it.first);
	}

	while(!childrenToCheck.empty()) {
		int current = *(childrenToCheck.begin());

		if(treePersons[current].parents.empty()) {
			childrenToCheck.erase(current);
			continue;
		}

		family element;

		for(int i = 0; i < treePersons[current].parents.size(); i++) {
			element.first.emplace(treePersons[current].parents[i]->id);
		}

		std::vector<treeBuilderElement*> parents = treePersons[current].parents;
		for(auto& it : parents[0]->childrens) {
			bool found = false;
			for(int i = 1; i < parents.size(); i++) {
				for(int j = 0; j < parents[i]->childrens.size(); j++) {
					if(parents[i]->childrens[j]->id == it->id) {
						found = true;
						break;
					}
				}
				if(!found)
					break;
			}
			if(!found)
				continue;

			element.second.emplace(it->id);
			childrenToCheck.erase(it->id);
		}

		value.push_back(element);
	}

	return value;
}
