#include "headers\block.h"

// -------------------------------------

void BlockNode::Evaluate() 
{
	unsigned int childrenCount = children.size();

	for(unsigned int i = 0; i < childrenCount; i++)
	{
		Node* child = children[i];

		child->Evaluate();

		delete child;
	}
}

// -------------------------------------

void BlockNode::addArg(std::string name, Type type)
{
	args.insert({name, type});
}

// void BlockNode::removeArg(std::string name)	
// {
	
// }

void BlockNode::addChild(Node* newChild)
{
	children.push_back(newChild);
	newChild->changeParent(this);
}

Node* BlockNode::getChild(unsigned int index)
{
	return children[index];
}

void BlockNode::removeChild(unsigned int index, bool del = false)
{
	if(del)
	{
		Node* child = children[index];
		delete child;
	}

	children.erase(children.begin() + index);
}

unsigned int BlockNode::childrenCount()
{
	return children.size();
}

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
	if(symbolTable[variableName]->type != newValue->type && !ignoreTypeCast)
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