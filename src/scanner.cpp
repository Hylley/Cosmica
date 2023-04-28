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

std::string findDataType(std::string& value)
{
	if(std::regex_match(value, booleano))
		return "bool";
		
	if(std::regex_match(value, inteiro))
		return "int";
	
	if(std::regex_match(value, flutuante))
		return "flut";
	
	if(std::regex_match(value, fita))
		return "fita";
	
	return nullptr;
}