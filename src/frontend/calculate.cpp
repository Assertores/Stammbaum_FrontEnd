#include "calculate.h"

std::set<int> GetAllPersons(const std::set<relation>& rels) {
	std::set<int> value;

	for(auto& it : rels) {
		value.emplace(it.objectID);
		value.emplace(it.subjectID);
	}

	return value;
}

std::set<int> GetAllPersons(const std::set<blood>& blds) {
	std::set<int> value;

	for(auto& it : blds) {
		value.emplace(it.objectID);
		value.emplace(it.subjectID);
	}

	return value;
}

std::set<int> GetAllPersons(const std::set<blood>& blds, const std::set<relation>& rels) {
	std::set<int> value;

	value = GetAllPersons(blds);
	value.merge(GetAllPersons(rels));

	return value;
}

tree CreateTree(const std::set<blood>& rels) {
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

generations SortPersons(tree& treePersons) {
	generations value;


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

std::pair<std::vector<std::vector<family>>, generations> SplitFamilysToGenerations(std::vector<family>& families, generations& peoples) {
	std::vector<std::vector<family>> value;
	generations additionalPeoples;

	additionalPeoples.push_back(std::set<int>());
	for(int i = 1; i < peoples.size(); i++) {
		value.push_back(std::vector<family>());
		additionalPeoples.push_back(std::set<int>());
	}

	for(int i = 0; i < families.size(); i++) {
		int parent = *(families[i].first.begin());
		for(int j = 0; j < peoples.size(); j++) {
			if(peoples[j].find(parent) != peoples[j].end()) {
				value[j].push_back(families[i]);
				for(auto& it : families[i].second) {
					family element;
					element.first.emplace(it);
					element.second.emplace(it);
					for(int serchGen = j + 1; serchGen < peoples.size() && peoples[serchGen].find(it) == peoples[serchGen].end(); serchGen++) {
						additionalPeoples[serchGen].emplace(it);
						value[serchGen].push_back(element);
					}
				}
				break;
			}
		}
	}

	return std::pair<std::vector<std::vector<family>>, generations>(value, additionalPeoples);
}

std::vector<family> CreatePlumbingInfos(std::vector<family>& families, visGen& upperGeneration, visGen& lowerGeneration) {

	std::vector<family> thisGeneration;
	for(int i = 0; i < families.size(); i++) {
		family element;
		for(auto& it : families[i].first) {
			int connection = 0;
			int j = 0;
			for(; upperGeneration[j].first != it; j++) {
				connection += upperGeneration[j].second.GetSize();
			}
			connection += upperGeneration[j].second.GetSize() / 2;//getConnection?
			if(upperGeneration[j].second.GetSize() <= 1)
				connection++;

			element.first.emplace(connection);
		}

		for(auto& it : families[i].second) {
			int connection = 0;
			int j = 0;
			for(; lowerGeneration[j].first != it; j++) {
				connection += lowerGeneration[j].second.GetSize();
			}
			connection += lowerGeneration[j].second.GetSize() / 2;//TODO: check for overlaps
			//if(lowerGeneration[j].second.GetSize() > 1)
				connection++;

			element.second.emplace(connection);
		}

		thisGeneration.push_back(element);
	}

	return thisGeneration;
}
