#include "headers/parser.h"

// Regular expressions pre-compilation

// Syntax
std::regex invisibles("^[ \t\n]*$");
std::regex tabs("^(\t*[ ]*).*");
std::regex singleLineComment("(\t*.*)[ ]*--[^\\[]+");			// Handle comments
std::regex multiLineComment[3] =
{
	std::regex ("(\t*.*)[ ]*--\\[\\[(.*)"), // Open comment
	std::regex ("(.*)\\]\\]$"),	// Close comment
	std::regex ("(.*)\\]\\].*")	// Incorrect close comment
};
std::regex ifCases[3] =
{
	std::regex ("^(\t*)se (.*):$"), 	// IF
	std::regex ("^(\t*)entretanto, se (.*):$"), 	// ELSE-IF
	std::regex ("^(\t*)senão:$") 	// ELSE
};
std::regex variableName("^[a-zA-Z0-9_À-ÖØ-öø-ÿ]+$");

// Operations
std::regex arithmeticOperator("^(\t*)(.*)[ ]*([+]|[-]|[*]|[/]|[%])[ ]*(.*)[ ]*$");

void Parse(std::string line, BlockNode& parent, std::string& fileName, int lineNumber, bool& isMultiCommented, std::unordered_map<unsigned int, BlockNode*>& tabtable)
{
	#if DEBUG_SHOW_LINES
	std::cout << "{line " << lineNumber << "} " << line << std::endl;
	#endif

	std::smatch matches;

	// Handle comments
	if(!isMultiCommented)
	{
		/*
			The single and multiple-lines regexes follow the same order:

				Index 0 -> Full text;

				Index 2 -> All chars after the opening sequence ("--" or "--[[")
				(not including the sequence itsel);

				Index 1 -> All chars between the beginning and the opening
				sequence (including tabs).

				What we need to do is basically reassing the line with the index 1 content,
			essencialy ignoring the comment part. Even if the content is empty, will be catch
			moreafer in the code.
		*/
		if(std::regex_match(line, matches, multiLineComment[0]))
		{
			line = matches[1];
			isMultiCommented = true;
		}
		if(std::regex_match(line, matches, singleLineComment))
		{
			line = matches[1];
		}
	}
	else
	{
		if(std::regex_match(line, matches, multiLineComment[1]))
		{
			isMultiCommented = false;
		}else if(std::regex_match(line, matches, multiLineComment[2]))
		{
			ThrowException(SyntaxError, fileName, lineNumber, "Fechamento de comentário precisa de linha exclusiva");
		}
		return;
	}

	// Handle empty lines
	if(std::regex_match(line, matches, invisibles))
		return;

	// Handle tabs
	unsigned int tabLevel = 0;
	if(std::regex_match(line, matches, tabs))
	{
		tabLevel = findTabLevel(matches[1], tabtable);
	}
	if(!tabtable.count(tabLevel))
		ThrowException(SyntaxError, fileName, lineNumber, "Não exite nenhum bloco encapsulando o nível " + std::to_string(tabLevel) + " de identação");
	

	if(std::regex_match(line, matches, arithmeticOperator))
	{
		tabtable[tabLevel]->addChild(generateArithmeticOperator(line, tabtable[tabLevel], fileName, lineNumber));

		unelevate(tabtable, tabLevel);
		return;
	}

	// if(std::regex_match(line, matches, ifCases[0]))
	// {
	// 	implementIf(matches, tabtable[tabLevel], fileName, lineNumber, tabtable , tabLevel);

	// 	return;
	// }


	ThrowException(SyntaxError, fileName, lineNumber, "Impossível resolver: \"" + line + "\"");

	return;
}

unsigned int findTabLevel(std::string tabs, std::unordered_map<unsigned int, BlockNode*>& tabtable)
{
	unsigned int tabLevel = 0;

	for (char c : tabs)
	{
		if(c != '\t')
			ThrowInternal("Identation only allowed with tabs!");
		
		tabLevel++;
	}

	return tabLevel;
}

void unelevate(std::unordered_map<unsigned int, BlockNode*>& tabtable, unsigned int tabLevel)
{
	for(const auto& pair : tabtable)
	{
		if(pair.first <= tabLevel)
			continue;
		
		tabtable.erase(pair.first);
	}
}