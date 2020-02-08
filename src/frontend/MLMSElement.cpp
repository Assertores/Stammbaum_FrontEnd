#include "MLMSElement.h"

MLMSElement::MLMSElement(std::string element, Boxing boxType/* = NoBox*/, char clearChar/* = ' '*/, unsigned int minSize/* = 0*/) {
	//https://stackoverflow.com/questions/13172158/c-split-string-by-line

	std::string::size_type pos = 0;
	std::string::size_type prev = 0;
	while((pos = element.find('\n', prev)) != std::string::npos) {
		lines.push_back(element.substr(prev, pos - prev));
		prev = pos + 1;
	}

	// To get the last substring (or only, if delimiter is not found)
	lines.push_back(element.substr(prev));

	//----- ----- end URL ----- -----

	size = minSize;
	for(size_t i = 0; i < lines.size(); i++) {
		size = (size > lines[i].length()) ? size : lines[i].length();
	}

	for(size_t i = 0; i < lines.size(); i++) {
		lines[i].append(size - lines[i].length(), clearChar);
	}

	emptyLine.clear();
	emptyLine.append(size, clearChar);

	if(boxType == NoBox)
		return;

	size += 2;
	emptyLine.append(2, clearChar);

	for(size_t i = 0; i < lines.size(); i++) {
		lines[i].insert(lines[i].begin(), '|'/*'│'*/);
		lines[i].append("|"/*"│"*/);
	}
	{
		std::string upperLine;
		upperLine.append("+"/*"┌"*/);
		upperLine.append(size - 2, '-'/*"─"*/);
		upperLine.append("+"/*"┐"*/);

		lines.insert(lines.begin(), upperLine);
	}
	{
		std::string lowerLine;
		lowerLine.append("+"/*"└"*/);
		lowerLine.append(size - 2, '-'/*"─"*/);
		lowerLine.append("+"/*"┘"*/);

		lines.push_back(lowerLine);
	}
}

int MLMSElement::GetSize() const {
	return size;
}

int MLMSElement::GetLineCount() {
	return lines.size();
}

std::string MLMSElement::GetLine(int line) {
	return line < lines.size() ? lines[line] : emptyLine;
}
