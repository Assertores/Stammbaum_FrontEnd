#pragma once

//===== ===== Extern ===== =====
#include <vector>
#include <set>

//===== ===== Intern ===== =====
#include "../utility/types.h"

std::set<int> GetAllPersons(std::set<relation>& rels);

std::set<int> GetAllPersons(std::set<blood>& blds);

std::set<int> GetAllPersons(std::set<blood>& blds, std::set<relation>& rels);

tree CreateTree(std::set<blood>& rels);

peoples SortPersons(tree& treePersons);

std::vector<family> CreatFamilies(tree& treePersons);

std::vector<std::vector<family>> CreatePlumbingInfos(std::vector<family>& families, std::vector<visGen>& treePeopleVisualisator);
