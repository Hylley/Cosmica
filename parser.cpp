#include "headers/parser.h"

// Regular expressions pre-compilation
std::regex invisibles("^[ \t\n]*$");
std::regex singleLineComment("(\t*)--[^\\[]+");			// Handle comments
std::regex multiLineComment[3] =
{
	std::regex ("(\t*)--\\[\\[(.*)"), // Open comment
	std::regex ("(.*)\\]\\]"),	// Correct close comment
	std::regex ("(.*)\\]\\](.*)")	// Incorrrect close comment
};
std::regex ifCase[3] =
{
	std::regex ("(\t*)se (.*):"), 	// IF
	std::regex ("(\t*)entretanto, se (.*):"), 	// ELSE-IF
	std::regex ("(\t*)entretanto:") 	// ELSE
};
std::regex variableAssign("(\t*)(.*)([ ]*)=([ ]*)(.*)");

void Parse(std::string& line, BlockNode& parent, std::string& fileName, int lineNumber, bool& isMultiCommented)
{
	#if DEBUG_SHOW_LINES
	std::cout << lineNumber << " " << line << std::endl;
	#endif

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

	// IF
	// if(std::regex_match(line, matches, ifCase[0]))
	// {
	// 	return;
	// }

	if(std::regex_match(line, matches, variableAssign))
	{
		std::string tabLevel = matches[1];
		std::string leftSide = matches[2];
		std::string rightSize = matches[5];
		
		#if DEBUG_DEVELOPER_FEEDBACK
		std::cout << tabLevel << std::endl;
		std::cout << leftSide << std::endl;
		std::cout << rightSize << std::endl;
		#endif

		if(rightSize.empty())
			ThrowException(ValueError, fileName, lineNumber, "\"" + rightSize + "\" não é uma declaração válida");


		std::vector<std::string> leftTokens = Tokenize(leftSide, ' ');
		unsigned int leftSideTokensSize = leftTokens.size();
		std::vector<std::string> rightTokens = Tokenize(rightSize, ' ');
		unsigned int rightSideTokensSize = rightTokens.size();

		if(leftSideTokensSize > 2 || leftSideTokensSize < 1)
			ThrowException(SyntaxError, fileName, lineNumber, "\"" + leftSide + "\" precisa seguir o parâmetro <data_type>* <variable_name>");
		if(rightSideTokensSize != 1)
			ThrowException(SyntaxError, fileName, lineNumber, "\"" + rightSize + "\" muitos valores para uma variável");

		// We have a explicit variable type
		std::string dataType;
		if(leftSideTokensSize == 2)
		{
			dataType = leftTokens[0];
		}else // We do not have explicit variable, so we need to figure it out
		{
			dataType = findDataType(rightSize);
		}

		if(!isValidDataType(leftTokens[0]))
			ThrowException(ValueError, fileName, lineNumber, "\"" + leftTokens[0] + "\" não é uma tipo de dado válido");
	
		#if DEBUG_DEVELOPER_FEEDBACK
		std::cout << "Explicit variable data type asign" << std::endl;
		#endif

		return;

		if(leftSideTokensSize == 1)
		
		// if(variableType.empty())
		// {
		// 	if(isInt(variableValue))
		// 	{

		// 	}
		// }else if(!isValidDataType(variableType))
		// {
		// 	ThrowException(TypeError, fileName, lineNumber, "\"" + variableType + "\" não é um tipo de dado válido");
		// }

		// parent.children.push_back(

		// );

		return;
	}

	if(std::regex_match(line, matches, invisibles))
		return;

	ThrowException(SyntaxError, fileName, lineNumber, "Impossível resolver: \"" + line + "\"");
}