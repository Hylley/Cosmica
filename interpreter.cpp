#include "headers\interpreter.h"

Node* generateOp(std::smatch& matches, std::string& fileName, int &lineNumber)
{
	std::string tabLevel = matches[1];
	std::string leftSide = matches[2];
	std::string op = matches[3];
	std::string rightSide = matches[4];

	if(rightSide.empty())
		ThrowException(ValueError, fileName, lineNumber, "\"" + rightSide + "\" não é uma declaração válida");

	Node* resultNode;

	// if(op == "=")
	// {

	// }
	// else if()
	// {
		
	// }

	return resultNode;
}

void implementIf(std::smatch& matches, BlockNode* parent, std::string& fileName, int &lineNumber, std::unordered_map<unsigned int, BlockNode*>& tabtable, int tabLevel)
{
	IfNode* node = new IfNode();
	tabtable[tabLevel + 1] = node;
	parent->addChild(node);
}