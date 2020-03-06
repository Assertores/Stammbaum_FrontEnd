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

void SortPersons(tree& treePersons) {
	for(auto& it : treePersons) {
		if(it.second.parents.size() <= 0)
			it.second.UpdateDown(0);
	}
}

generations GenerateGenerationsFromTree(const tree& treePersons) {
	generations value;

	{
		int max = -1;
		for(auto& it : treePersons) {
			max = max > it.second.number ? max : it.second.number;
		}

		for(int i = 0; i < max + 1; i++) {
			value.push_back(std::vector<int>());
		}
	}

	for(auto& it : treePersons) {
		value[it.second.number].push_back(it.first);
	}

	return value;
}

std::vector<family> CreatFamilies(const tree& treePersons) {
	std::vector<family> value;

	std::set<int> childrenToCheck;
	for(auto& it : treePersons) {
		childrenToCheck.emplace(it.first);
	}

	while(!childrenToCheck.empty()) {
		int current = *(childrenToCheck.begin());

		if(treePersons.at(current).parents.empty()) {
			childrenToCheck.erase(current);
			continue;
		}

		family element;

		for(int i = 0; i < treePersons.at(current).parents.size(); i++) {
			element.first.emplace(treePersons.at(current).parents[i]->id);
		}

		const std::vector<treeBuilderElement*> parents = treePersons.at(current).parents;
		for(auto& it : parents[0]->childrens) {

			bool found = true;
			for(int i = 1; i < parents.size(); i++) {
				found = false;
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

struct personSortInfos {
	int id;
	int pos;
	int upperFamMinPos;
	int upperFamMaxPos;
	int lowerFamMinPos;
	int lowerFamMaxPos;

	int operator - (const personSortInfos& rhs) {
		int lhsCurrent = 0;
		int rhsCurrent = 0;
		int lhsGain = 0;
		int rhsGain = 0;

		if(upperFamMaxPos > 0) {
			lhsGain += (rhs.pos < upperFamMinPos) ? -rhs.pos + upperFamMinPos : 0;
			lhsGain += (rhs.pos > upperFamMaxPos) ? +rhs.pos - upperFamMaxPos : 0;

			lhsCurrent += (pos < upperFamMinPos) ? -pos + upperFamMinPos : 0;
			lhsCurrent += (pos > upperFamMaxPos) ? +pos - upperFamMaxPos : 0;
		}
		if(lowerFamMaxPos > 0) {
			lhsGain += (rhs.pos < lowerFamMinPos) ? -rhs.pos + lowerFamMinPos : 0;
			lhsGain += (rhs.pos > lowerFamMaxPos) ? +rhs.pos - lowerFamMaxPos : 0;

			lhsCurrent += (pos < lowerFamMinPos) ? -pos + lowerFamMinPos : 0;
			lhsCurrent += (pos > lowerFamMaxPos) ? +pos - lowerFamMaxPos : 0;
		}

		if(rhs.upperFamMaxPos > 0) {
			rhsGain += (pos < rhs.upperFamMinPos) ? -pos + rhs.upperFamMinPos : 0;
			rhsGain += (pos > rhs.upperFamMaxPos) ? +pos - rhs.upperFamMaxPos : 0;

			rhsCurrent += (rhs.pos < rhs.upperFamMinPos) ? -rhs.pos + rhs.upperFamMinPos : 0;
			rhsCurrent += (rhs.pos > rhs.upperFamMaxPos) ? +rhs.pos - rhs.upperFamMaxPos : 0;
		}
		if(rhs.lowerFamMaxPos > 0) {
			rhsGain += (pos < rhs.lowerFamMinPos) ? -pos + rhs.lowerFamMinPos : 0;
			rhsGain += (pos > rhs.lowerFamMaxPos) ? +pos - rhs.lowerFamMaxPos : 0;

			rhsCurrent += (rhs.pos < rhs.lowerFamMinPos) ? -rhs.pos + rhs.lowerFamMinPos : 0;
			rhsCurrent += (rhs.pos > rhs.lowerFamMaxPos) ? +rhs.pos - rhs.lowerFamMaxPos : 0;
		}

		return (lhsCurrent + rhsCurrent) - (lhsGain + rhsGain);
	}
};

bool SortGeneration(const std::vector<int>* upperGeneration, const std::vector<family>* upperFamilies, std::vector<int>& currentGeneration, const std::vector<family>* lowerFamilies, const std::vector<int>* lowerGeneration) {
	bool hasTargetChanged = false;

	std::vector<personSortInfos> curGenSortInfos;

	for(int i = 0; i < currentGeneration.size(); i++) {
		personSortInfos element;
		element.id = currentGeneration[i];
		element.pos = i;
		if(upperGeneration == nullptr || upperFamilies == nullptr) {
			element.upperFamMaxPos = -1;
			element.upperFamMinPos = -1;
		} else {
			element.upperFamMaxPos = INT_MIN;
			element.upperFamMinPos = INT_MAX;

			for(int i = 0; i < upperFamilies->size(); i++) {
				if((*upperFamilies)[i].second.find(element.id) != (*upperFamilies)[i].second.end())
					continue;
				
				//found a familie
				for(auto& it : (*upperFamilies)[i].first) {
					int pos = FindInVector(*upperGeneration, it);

					element.upperFamMaxPos = (pos > element.upperFamMaxPos) ? element.upperFamMaxPos : pos;
					element.upperFamMinPos = (pos < element.upperFamMinPos) ? pos : element.upperFamMinPos;
				}
				for(auto& it : (*upperFamilies)[i].second) {
					int pos = FindInVector(*upperGeneration, it);

					element.upperFamMaxPos = (pos > element.upperFamMaxPos) ? element.upperFamMaxPos : pos;
					element.upperFamMinPos = (pos < element.upperFamMinPos) ? pos : element.upperFamMinPos;
				}
			}
		}
		if(lowerGeneration == nullptr || lowerFamilies == nullptr) {
			element.lowerFamMaxPos = -1;
			element.lowerFamMinPos = -1;
		} else {
			element.lowerFamMaxPos = INT_MIN;
			element.lowerFamMinPos = INT_MAX;

			for(int i = 0; i < lowerFamilies->size(); i++) {
				if((*lowerFamilies)[i].first.find(element.id) == (*lowerFamilies)[i].first.end())
					continue;

				//found a familie
				for(auto& it : (*lowerFamilies)[i].first) {
					int pos = FindInVector(*lowerGeneration, it);

					element.lowerFamMaxPos = (pos > element.lowerFamMaxPos) ? element.lowerFamMaxPos : pos;
					element.lowerFamMinPos = (pos < element.lowerFamMinPos) ? pos : element.lowerFamMinPos;
				}
				for(auto& it : (*lowerFamilies)[i].second) {
					int pos = FindInVector(*lowerGeneration, it);

					element.lowerFamMaxPos = (pos > element.lowerFamMaxPos) ? element.lowerFamMaxPos : pos;
					element.lowerFamMinPos = (pos < element.lowerFamMinPos) ? pos : element.lowerFamMinPos;
				}
			}
		}

		curGenSortInfos.push_back(element);
	}

	for(int predator = 0; predator < curGenSortInfos.size() - 1; predator++) {
		int max = 0;
		int maxIndex = predator;

		for(int victim = predator + 1; victim < curGenSortInfos.size(); victim++) {
			int improvement = curGenSortInfos[victim] - curGenSortInfos[predator];

			if(max >= improvement)
				continue;

			hasTargetChanged = true;
			max = improvement;
			maxIndex = victim;
		}

		if(max > 0) {
			//TODO: can be inproved by only cecking upto the last changed element until reached and continue for loop from there
			predator = -1; //will be 0 in next cyklus through predator++ in for loop

			int tmpPos = curGenSortInfos[maxIndex].pos;
			curGenSortInfos[maxIndex].pos = curGenSortInfos[predator].pos;
			curGenSortInfos[predator].pos = tmpPos;
			//TODO: recalculate

			personSortInfos tmpPers = curGenSortInfos[maxIndex];
			curGenSortInfos[maxIndex] = curGenSortInfos[predator];
			curGenSortInfos[predator] = tmpPers;
		}
	}

	if(hasTargetChanged) {
		for(int i = 0; i < currentGeneration.size(); i++) {
			currentGeneration[i] = curGenSortInfos[i].id;
		}
	}

	return hasTargetChanged;
}

std::pair<std::vector<std::vector<family>>, generations> SplitFamilysToGenerations(const std::vector<family>& families, const generations& peoples) {
	std::vector<std::vector<family>> value;
	generations additionalPeoples;

	additionalPeoples.push_back(std::vector<int>());
	for(int i = 1; i < peoples.size(); i++) {
		value.push_back(std::vector<family>());
		additionalPeoples.push_back(std::vector<int>());
	}

	for(int i = 0; i < families.size(); i++) {
		int parent = *(families[i].first.begin());
		for(int j = 0; j < peoples.size(); j++) {
			if(!ExistsInVector(peoples[j], parent))
				continue;

			value[j].push_back(families[i]);
			for(auto& it : families[i].second) {
				family element;
				element.first.emplace(it);
				element.second.emplace(it);
				for(int serchGen = j + 1; serchGen < peoples.size() && !ExistsInVector(peoples[serchGen], it); serchGen++) {
					additionalPeoples[serchGen].push_back(it);
					value[serchGen].push_back(element);
				}
			}
			break;
		}
	}

	return std::pair<std::vector<std::vector<family>>, generations>(value, additionalPeoples);
}

std::vector<family> CreatePlumbingInfos(const std::vector<family>& families, const visGen& upperGeneration, const visGen& lowerGeneration) {

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
