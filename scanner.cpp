#include "headers/scanner.h"

std::vector<std::vector<std::string>> GetTokens(std::string rawContent)
{
	std::vector<std::vector<std::string>> lines; // To clarify: a vector of string vectors
	
	std::istringstream fileStream(rawContent);
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

	std::string token;
	for(int i = 0; i < length; i++)
	{
		char character = line[i];
		if(character == ' ')
		{
			tokens.push_back(std::string());
			continue;
		}

		tokens.back() = tokens.back() + character;
	}

	return tokens;
}