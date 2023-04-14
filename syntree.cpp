#include "headers/syntree.h"

unsigned int Node::getType()
{
	return nodeType;
}

void Node::changeParent(Node* newParent)
{
	parent = newParent;
}

// ------------------------

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

void BlockNode::changeVariable(std::string variableName, LiteralNode* newValue)
{
	if(!hasVariable(variableName))
		ThrowInternal("You're trying to change a variable that doesn't exist u idiot (syntree.cpp, line 64)");

	LiteralNode* oldValue = symbolTable[variableName];
	symbolTable[variableName] = newValue;

	#if DEBUG_SHOW_VARIABLES_CHANGES
	std::cout << "{ " + variableName + ',' + oldValue->value + " } (deleted)" << std::endl;
	std::cout << "{ " + variableName + ',' + newValue->value + " } (new)" << std::endl;
	#endif

	delete oldValue;
}

void BlockNode::addVariable(std::string variableName, LiteralNode* newValue)
{
	symbolTable[variableName] = newValue;

	#if DEBUG_SHOW_VARIABLES_CHANGES
	std::cout << "{ " + variableName + ", " + newValue->value + " }" << std::endl;
	#endif
}

void LiteralNode::SetType(std::string newType)
{
	if(newType == "bool") { type = Type::BOOL; return; }
	if(newType == "int" ) { type = Type::INT; return;  }
	if(newType == "flut") { type = Type::FLUT; return; }
	if(newType == "fita") { type = Type::FITA; return; }

	ThrowInternal("No valid type provided at variable asign (syntree.cpp, line 92)");
}