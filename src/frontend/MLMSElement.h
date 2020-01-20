#pragma once
//#pragma execution_character_set("utf-8")

//===== ===== Extern ===== =====
#include <string>
#include <vector>

//===== ===== Intern ===== =====

enum Boxing {
	NoBox = 0,
	Box = 1,
	BoxUpperPort = 3,
	BoxLowerPort = 5,
	BoxUpALoPort = 7,
};

// Multy Line Mono Size Element
class MLMSElement {
public:
	MLMSElement(std::string element, Boxing boxType = NoBox, unsigned int minSize = 0);

	int GetSize();
	int GetLineCount();
	std::string GetLine(int line);

private:
	std::string emptyLine;
	std::vector<std::string> lines;
	unsigned int size = 0;
};