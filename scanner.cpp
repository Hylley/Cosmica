#include "headers/scanner.h"

// Regular expressions pre-compilation
std::regex invisibles("^[ \t\n]*$");
std::regex singleLineComment("(\t*)--[^\\[]+");			// Handle comments
std::regex multiLineComment[3] = {
	std::regex ("(\t*)--\\[\\[(.*)"), // Open comment
	std::regex ("(.*)\\]\\]"),	// Correct close comment
	std::regex ("(.*)\\]\\](.*)")	// Incorrrect close comment
};
std::regex se("(\t*)se (.*):");				// Handle IFs
std::regex variableAssign("(\t*)(int|cadeia|flut|bool)?(.*)=[ ]*([^ ]*)");

void ScanLine(std::string& line, BlockNode&	parent, std::string& fileName, int lineNumber, bool& isMultiCommented)
{
	std::smatch matches;
	
	// Handle comments
	if(std::regex_match(line, matches, singleLineComment))
		return;
	if(std::regex_match(line, matches, multiLineComment[0]) && !isMultiCommented)
	{
		isMultiCommented = true;
		return;
	}
	if(std::regex_match(line, matches, multiLineComment[1]) && isMultiCommented)
	{
		isMultiCommented = false;
		return;
		
	}else if(std::regex_match(line, matches, multiLineComment[2]) && isMultiCommented)
	{
		isMultiCommented = false;
	}

	if(isMultiCommented)
		return;

	// Handle IF
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
		ScanLine(line, parent, fileName, ++lineCount, isMultiCommented);
	}
}