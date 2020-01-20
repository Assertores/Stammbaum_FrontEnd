#include "MLMSElement.h"

MLMSElement::MLMSElement(std::string element, Boxing boxType/* = NoBox*/, unsigned int minSize/* = 0*/) {
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
	for(int i = 0; i < lines.size(); i++) {
		size = (size > lines[i].length()) ? size : lines[i].length();
	}

	for(int i = 0; i < lines.size(); i++) {
		for(int j = lines[i].length(); j < size; j++) {
			lines[i].append(" ");
		}
	}

	emptyLine.clear();
	for(int i = 0; i < size; i++)
		emptyLine.append(" ");

	if(boxType == NoBox)
		return;

	size += 2;
	emptyLine.append("  ");

	for(int i = 0; i < lines.size(); i++) {
		lines[i].insert(lines[i].begin(), '|'/*'│'*/);
		lines[i].append("|"/*"│"*/);
	}
	{
		std::string upperLine;
		upperLine.append("+"/*"┌"*/);
		for(int i = 1; i < size - 1; i++) {
			upperLine.append("-"/*"─"*/);
		}
		upperLine.append("+"/*"┐"*/);

		lines.insert(lines.begin(), upperLine);
	}
	{
		std::string lowerLine;
		lowerLine.append("+"/*"└"*/);
		for(int i = 1; i < size - 1; i++) {
			lowerLine.append("-"/*"─"*/);
		}
		lowerLine.append("+"/*"┘"*/);

		lines.push_back(lowerLine);
	}
}

int MLMSElement::GetSize() {
	return size;
}

int MLMSElement::GetLineCount() {
	return lines.size();
}

std::string MLMSElement::GetLine(int line) {
	return line < lines.size() ? lines[line] : emptyLine;
}