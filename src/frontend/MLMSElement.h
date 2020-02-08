#pragma once
//#pragma execution_character_set("utf-8")

//===== ===== Extern ===== =====
#include <string>
#include <vector>

//===== ===== Intern ===== =====

/*!
 * The type of boxing, that should be used
 * use || to combine multiple elements
 */
enum Boxing {
	NoBox = 0,			/*!< wont add anithing */
	Box = 1,			/*!< drawns a box with no ports around */
	UpperPort = 2,		/*!< adds a port on the top of the box */
	LowerPort = 4,		/*!< adds a port on the bottom of the box */
};

/*!
 * Multy Line Mono Size Element
 * can take a multiline string and return it line by line in mono length for printing onto the console
 */
class MLMSElement {
public:
	/*!
	 * @brief			no uninitialiced objects
	 * @param element	the multiline string
	 * @param boxType	the combined boxing type (see enum \link Boxing \endlink)
	 * @param clearChar	the char to use for padding
	 * @param minSize	the minimal line length
	 */
	MLMSElement(std::string element, Boxing boxType = NoBox, char clearChar = ' ', unsigned int minSize = 0);

	/*!
	 * @return	the actual line length nedded to draw the object
	 * @remarks	is const
	 */
	int GetSize() const;

	/*!
	 * @return	the minimal count of lines needed to draw the object
	 * @remarks	is const
	 */
	int GetLineCount() const;

	/*!
	 * @brief				access the content of the object
	 * @param line			the line to be returned
	 * @return				the requested line
	 * @retval emptyLine	if the line is out of range
	 */
	std::string GetLine(const int line);

private:
	std::string emptyLine;
	std::vector<std::string> lines;
	unsigned int size = 0;
};