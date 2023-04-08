#include "headers/scanner.h"

std::vector<std::vector<std::string>> Lexer(std::string raw)
{
	std::vector<std::vector<std::string>> lines; // To clarify: a vector of string vectors
	
	std::istringstream fileStream(raw);
	std::string line;
	while(std::getline(fileStream, line))
	{
		lines.push_back(SplitLine(line));
	}

	return lines;
}

std::vector<std::string> SplitLine(std::string &line)
{
	int length = line.length();
	std::vector<std::string> tokens;
	tokens.push_back(std::string());

	bool isString = false;
	for(int i = 0; i < length; i++)
	{
		char character = line[i];

		if(character == '\'' || character == '\"')
		{
			isString = !isString;
		}

		// Hardcoded else-if but I DON'T CARE OK, IF IT WORKS, IT WORKS
		if(character == ' ' &&  !isString && tokens.back() != "entretanto,")
		{
			tokens.push_back(std::string());
			continue;
		}

		tokens.back() = tokens.back() + character;
	}

	return tokens;
}