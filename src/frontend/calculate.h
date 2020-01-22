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

generations SortPersons(tree& treePersons);

std::vector<family> CreatFamilies(tree& treePersons);

std::pair<std::vector<std::vector<family>>, generations> SplitFamilysToGenerations(std::vector<family>& families, generations& peoples);

std::vector<family> CreatePlumbingInfos(std::vector<family>& families, visGen& upperGeneration, visGen& lowerGeneration);
