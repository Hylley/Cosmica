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
std::regex variableAssign("(\t*)(.*)([ ]*)=([ ]*)(.*)");
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
		std::string tabLevel = matches[1];
		std::string leftSide = matches[2];
		std::string rightSize = matches[5];

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
		std::string variableName;
		std::string dataType;
		std::string variableValue = rightTokens[0];

		if(leftSideTokensSize == 2)
		{
			if(!isValidDataType(leftTokens[0]))
				ThrowException(ValueError, fileName, lineNumber, "\"" + leftTokens[0] + "\" não é um tipo de dado válido");
			if(leftTokens[0] != findDataType(variableValue))
				ThrowException(ValueError, fileName, lineNumber, "\"" + leftTokens[0] + "\" e " + variableValue + " não correspondem ao mesmo tipo");

			dataType = leftTokens[0];
			variableName = leftTokens[1];
		}else // We do not have explicit variable, so we need to figure it out
		{
			variableName = leftTokens[0];
			dataType = findDataType(variableValue);

			if(dataType == "null")
				ThrowException(ValueError, fileName, lineNumber, "\"" + variableValue + "\" não é um tipo de dado válido");
		}

		if(isdigit(variableName[0]))
			ThrowException(SyntaxError, fileName, lineNumber, "Nomes de variável (\"" + variableName + "\") só podem começar com caracteres alfabéticos ou \"_\"");
		if(!std::regex_match(variableName, validVariableName))
			ThrowException(SyntaxError, fileName, lineNumber, "Nomes de variável (\"" + variableName + "\") só podem conter caracteres alfanuméricos ou \"_\"");
		if (std::find(std::begin(reserved_keywords), std::end(reserved_keywords), variableName) != std::end(reserved_keywords))
			ThrowException(SyntaxError, fileName, lineNumber, "\"" + variableName + "\" é uma palavra reservada");

		// DAANGER ZONE DANGER ZONE MEMORY LEAK ALLERT!!!!!
		VariablAssign* node = new VariablAssign();
		LiteralNode* literal = new LiteralNode();
		literal->SetType(dataType);
		literal->value = variableValue;
		node->name = variableName;
		node->literal = literal;
		
		parent.addChild(node);

		return;
	}

	
	
	ThrowException(SyntaxError, fileName, lineNumber, "Impossível resolver: \"" + line + "\"");

	return;
}