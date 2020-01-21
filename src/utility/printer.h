#pragma once
//#pragma execution_character_set("utf-8")

//===== ===== Extern ===== =====
#include <sstream>
#include <chrono>
#include <ctime>
#include <set>
#include <vector>

//===== ===== Intern ===== =====
#include "types.h"

/// <summary>
/// returns a human readable string of the type
/// </summary>
cString relToString(const relType t);

/// <summary>
/// returns a symble of the type
/// </summary>
char relToChar(const relType t);

/// <summary>
/// returns a human readable string of the type
/// </summary>
cString sexToString(const sexType t);

/// <summary>
/// returns a symble of the type
/// </summary>
char sexToChar(const sexType t);

/// <summary>
/// returns the person as human readable string
/// </summary>
std::string PersonToString(const personInfos person, bool longVariant = true);

/// <summary>
/// returns the person as human readable string
/// a list of families
/// a familie contains all connection above (parents) and all connection below (children)
/// the numbers are the charcount of the connection
/// </summary>
std::string PlumbGeneration(std::vector<std::pair<std::set<int>, std::set<int>>>& families);
