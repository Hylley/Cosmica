#include "headers/scanner.h"

std::vector<std::string> Lexer(std::string&	raw, BlockNode&	parent,	std::string& fileName)
{
	std::istringstream fileStream(raw);
	std::string	line;
	bool isMultiCommented =	false;
	int	lineCount =	0;
	while(std::getline(fileStream, line))
	{
		Parse(line,	parent,	fileName, ++lineCount, isMultiCommented);
	}
}

//Not only tokenize the string, but also trim irrelevant spaces in the surroundings
std::vector<std::string> Tokenize(std::string const	&str, const	char delimiter)
{
	std::vector<std::string> out;
	std::stringstream stringStream(str);

	std::string	s;
	while (std::getline(stringStream,	s, delimiter)) {	
		out.push_back(s); 
	}

	return out;
}

std::string findDataType(std::string& input)
{
	
}

bool isValidDataType(std::string& value)
{
	return value == "int" || value == "flut"|| value == "cadeia" || value == "bool";
}