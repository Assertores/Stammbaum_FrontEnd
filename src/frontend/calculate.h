#pragma once

//===== ===== Extern ===== =====
#include <vector>
#include <set>
#include <map>

//===== ===== Intern ===== =====
#include "../utility/types.h"
#include "treeBuilderElement.h"

std::set<int> GetAllPersons(std::set<relation>& rels);

std::set<int> GetAllPersons(std::set<blood>& blds);

std::set<int> GetAllPersons(std::set<blood>& blds, std::set<relation>& rels);

std::map<int, treeBuilderElement> CreateTree(std::set<blood>& rels);

std::vector<std::set<int>> SortPersons(std::map<int, treeBuilderElement>& treePersons);

std::vector<std::pair<std::set<int>, std::set<int>>> CreatFamilies(std::map<int, treeBuilderElement>& treePersons);
