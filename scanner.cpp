#include "headers/scanner.h"

void Lexer(std::string&	raw, BlockNode&	parent,	std::string& fileName)
{
	std::istringstream fileStream(raw);
	std::string	line;
	bool isMultiCommented =	false;
	int	lineCount =	0;
	std::unordered_map<unsigned int, BlockNode*> tabtable =
	{
		{0, &parent}
	};
	
	while(std::getline(fileStream, line))
	{
		Parse(line,	parent,	fileName, ++lineCount, isMultiCommented, tabtable);
	}
}

//Not only tokenize the string, but also trim irrelevant spaces in the surroundings
std::vector<std::string> Tokenize(std::string &str, char delimiter)
{
	std::vector<std::string> out;
	std::string sufix;

	// If there is a string
	std::smatch matches;
	if(std::regex_match(str, matches, stringLiteral))
	{
		str = matches[1];
		sufix = matches[2];
		sufix.back() = '\'';
		sufix = '\'' + sufix;
	}

	std::stringstream stringStream(str);
	std::string	s;
	
	while (std::getline(stringStream, s, delimiter)) {	
		out.push_back(s); 
	}

	if(!sufix.empty())
		out.push_back(sufix);

	return out;
}

std::string findDataType(std::string& value)
{
	if(value == "sim" || value == "não" || value == "verdadeiro" || value == "falso" || value == "crocodilo")
		return "bool";
		
	if(std::regex_match(value, std::regex("^[0-9]+$")))
		return "int";
	
	if(std::regex_match(value, std::regex("(([0-9]+)?.[0-9]+f?)|([0-9]+f)")))
		return "flut";
	
	if(std::regex_match(value, std::regex("\'(.*)\n*(.*)\'")))
		return "fita";
	
	return "null";
}

bool isValidDataType(std::string& value)
{
	return value == "int" || value == "flut"|| value == "fita" || value == "bool";
}

bool isInt(std::string& value)
{
	return std::regex_match(value, std::regex("^[0-9]+$"));
}

bool isFloat(std::string& value)
{
	return std::regex_match(value, std::regex("(([0-9]+)?.[0-9]+f?)|([0-9]+f)"));
}