#include "..\..\headers\syntree\block.h"

// -------------------------------------

void BlockNode::Evaluate() 
{
	unsigned int childrenCount = children.size();

	for(unsigned int i = 0; i < childrenCount; i++)
	{
		EvaluationNode* child = dynamic_cast<EvaluationNode*>(children[i]);
		child->Evaluate();

		delete child;
	}
}

// -------------------------------------

bool BlockNode::hasVariable(std::string variableName)
{
	return symbolTable.count(variableName);
}

LiteralNode* BlockNode::getVariable(std::string variableName)
{
	return symbolTable[variableName];
}

void BlockNode::changeVariable(std::string variableName, LiteralNode* newValue, bool ignoreTypeCast = false)
{
	if(!hasVariable(variableName))
		ThrowInternal("You're trying to change a variable that doesn't exist u idiot (syntree.cpp, line 64)");
	if(symbolTable[variableName]->getType() != newValue->getType() && !ignoreTypeCast)
		ThrowInternal('(' + newValue->value + ") does not share the same type as \"" + variableName + '\"');

	LiteralNode* oldValue = symbolTable[variableName];
	symbolTable[variableName] = newValue;

	#if DEBUG_SHOW_VARIABLES_CHANGES
	std::cout << "(-) { " + variableName + ", " + oldValue->value + " }" << std::endl;
	std::cout << "(+) { " + variableName + ", " + newValue->value + " }" << std::endl;
	#endif

	delete oldValue;
}

void BlockNode::addVariable(std::string variableName, LiteralNode* newValue)
{
	symbolTable[variableName] = newValue;

	#if DEBUG_SHOW_VARIABLES_CHANGES
	std::cout << "(+) { " + variableName + ", " + newValue->value + " }" << std::endl;
	#endif
}