#include "headers/scanner.h"

// REGEX PATTERNS
std::regex se("(\t*)se (.*):"); // If
std::regex variableAssign("(\t*)(int|cadeia|flut|bool)?(.*)=[ ]*([^ ]*)");
std::regex invisibles("^[ \t\n]*$");

void ScanLine(std::string& line, BlockNode&	parent, std::string& fileName, int lineNumber)
{
	std::smatch matches;
	if(std::regex_match(line, matches, se))
	{
		std::cout << matches[0] << std::endl;

		return;
	}

	if(std::regex_match(line, matches, variableAssign))
	{
		std::cout << matches[0] << std::endl;

		return;
	}

	if(std::regex_match(line, matches, invisibles))
		return;

	ThrowException(SyntaxError, fileName, lineNumber, "Could not resolve: \"" + line + "\"");
}

std::vector<std::string> Lexer(std::string&	raw, BlockNode&	parent, std::string& fileName)
{
	std::istringstream fileStream(raw);
	std::string	line;
	bool isMultiCommented =	false;
	int lineCount = 0;
	while(std::getline(fileStream, line))
	{
		ScanLine(line, parent, fileName, ++lineCount);
	}
}