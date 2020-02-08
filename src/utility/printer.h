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

/*!
 * @param[in] t	the type of the relation
 * @return		a human readable string of \p t
*/
cString relToString(const relType t);

/*!
 * @param[in] t	the type of the relation
 * @return		a symble of \p t
 */
char relToChar(const relType t);

/*!
 * @param[in] t	the sex
 * @return		a human readable string of \p t
 */
cString sexToString(const sexType t);

/*!
 * @param[in] t	the sex
 * @return		a symble of \p t
 */
char sexToChar(const sexType t);

/*!
 * @param[in] person		the informations to the person
 * @param[in] longVariant	wheter the informations should be compressed or not
 * @return					the person as human readable string
 */
std::string PersonToString(const personInfos person, bool longVariant = true);

/*!
 * @param[in] families	a list of families (the numbers are the charcount of the connection)
 * @return				the person as human readable string
 */
std::string PlumbGeneration(const std::vector<family>& families);
