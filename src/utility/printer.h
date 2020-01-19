#pragma once

//===== ===== Extern ===== =====
#include <sstream>
#include <chrono>
#include <ctime>

//===== ===== Intern ===== =====
#include "types.h"

/// <summary>
/// returns a human readable string of the type
/// </summary>
cString relToString(relType t);

/// <summary>
/// returns a symble of the type
/// </summary>
char relToChar(relType t);

/// <summary>
/// returns a human readable string of the type
/// </summary>
cString sexToString(sexType t);

/// <summary>
/// returns a symble of the type
/// </summary>
char sexToChar(sexType t);

/// <summary>
/// returns the person as human readable string
/// </summary>
std::string PersonToString(personInfos person, bool longVariant = true);
