#include "headers\interpreter.h"

void implementVariableAssign(std::smatch& matches, BlockNode* parent, std::string& fileName, int &lineNumber)
{
	std::string tabLevel = matches[1];
	std::string assignOp = matches[3];
	std::string leftSide = matches[2];
	std::string rightSize = matches[4];

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
	literal->setTypeStr(dataType);
	literal->value = variableValue;
	node->name = variableName;
	node->literal = literal;
	if(assignOp == "<-")
		node->ignoreTypeCast = true;
	
	parent->addChild(node);

	return;
}

void implementIf(std::smatch& matches, BlockNode* parent, std::string& fileName, int &lineNumber, std::unordered_map<unsigned int, BlockNode*>& tabtable, int tabLevel)
{
	std::string condition = matches[2];
}