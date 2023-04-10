#include "headers/scanner.h"

bool verifyBeyond(std::string fullLine, int pivotIndex, std::string verifier)
{
	if(fullLine.length() < pivotIndex + (verifier.length() - 1))
		return false;
	
	unsigned int length = verifier.length();
	for(int i = 0; i < length; i++)
	{
		if(fullLine[pivotIndex + i] != verifier[i])
			return false;
	}

	return true;
}

void ConcatCharWithTheLastToken(std::vector<std::string>& vector, char character)
{
	vector.back() = vector.back() + character;
}

void CreateNewToken(std::vector<std::string>& vector)
{
	vector.push_back(std::string(""));
}

std::vector<std::string> ScanLine(std::string& line, bool& isMultiCommented)
{
	std::cout << line << std::endl;

	int length = line.length();
	std::vector<std::string> tokens;
	return tokens;
	tokens.push_back(std::string());

	bool isString = false;
	for(int i = 0; i < length; i++)
	{
		char character = line[i];

		if(character == '\'' || character == '\"')
		{
			isString = !isString;
			
			if(!isString)
			{
				ConcatCharWithTheLastToken(tokens, character);
				CreateNewToken(tokens);
				continue;
			}
		}

		// If we're interating through a string, concat everything until isn't anymore.
		if(isString)
		{
			ConcatCharWithTheLastToken(tokens, character);
			continue;
		}


		// Strings will never pass through the rest of this code, so for now on, it's safe.


		// Early split in spaces
		if(character == ' ' && tokens.back() != "entretanto,")
		{
			CreateNewToken(tokens);
			continue;			
		}

		// Characters thta will split the string, but not included in the final result
		if(character == '(')
		{
			CreateNewToken(tokens);
			continue;
		}

		ConcatCharWithTheLastToken(tokens, character);

		// Characters that will split the string and be included in the final result
		if(false)
		{
			CreateNewToken(tokens);
		}
	}

	return tokens;
}

std::vector<std::vector<std::string>> Lexer(std::string raw)
{
	std::vector<std::vector<std::string>> lines; // To clarify: a vector of string vectors
	
	std::istringstream fileStream(raw);
	std::string line;
	bool isMultiCommented = false;
	while(std::getline(fileStream, line))
	{
		lines.push_back(ScanLine(line, isMultiCommented));
	}
	return lines;
}