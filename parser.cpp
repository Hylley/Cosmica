#include "headers/parser.h"

// Regular expressions pre-compilation
std::regex invisibles("^[ \t\n]*$");
std::regex singleLineComment("(\t*.*)[ ]*--[^\\[]+");			// Handle comments
std::regex multiLineComment[3] =
{
	std::regex ("(\t*.*)[ ]*--\\[\\[(.*)"), // Open comment
	std::regex ("(.*)\\]\\]"),	// Correct close comment
	std::regex ("(.*)\\]\\](.*)")	// Incorrrect close comment
};
std::regex stringLiteral("(.*)((\'(.*)\n*(.*)\')|(\"(.*)\n*(.*)\"))([ ]*)");
std::regex ifCase[3] =
{
	std::regex ("(\t*)se (.*):"), 	// IF
	std::regex ("(\t*)entretanto, se (.*):"), 	// ELSE-IF
	std::regex ("(\t*)entretanto:") 	// ELSE
};
std::regex variableAssign("(\t*)(.*)[ ]*(=|<-)[ ]*(.*)");
std::regex validVariableName("^[a-zA-Z0-9_À-ÖØ-öø-ÿ]+$");

void Parse(std::string line, BlockNode& parent, std::string& fileName, int lineNumber, bool& isMultiCommented)
{
	#if DEBUG_SHOW_LINES
	std::cout << lineNumber << " " << line << std::endl;
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
			ThrowException(SyntaxError, fileName, lineNumber, "Fechamento de comentário precisa de linha exclusiva.");
		}

		return;
	}

	if(std::regex_match(line, matches, invisibles))
		return;

	if(std::regex_match(line, matches, variableAssign))
	{
		implementVariableAssign(matches, parent, fileName, lineNumber);

		return;
	}

	
	
	ThrowException(SyntaxError, fileName, lineNumber, "Impossível resolver: \"" + line + "\"");

	return;
}