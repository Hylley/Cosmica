#include "headers/syntree.h"

bool BlockNode::hasVariableInPool(std::string variableName)
{
	return symbolTable.count(variableName);
}

LiteralNode* BlockNode::getVariableInPool(std::string variableName)
{
	return symbolTable[variableName];
}

void BlockNode::changeVariableInPool(std::string variableName, LiteralNode* newValue)
{
	LiteralNode* oldValue = symbolTable[variableName];
	symbolTable[variableName] = newValue;
	delete oldValue;

}

void BlockNode::addVariableInPool(std::string variableName, LiteralNode* newValue)
{
	symbolTable[variableName] = newValue;
}


void LiteralNode::SetType(std::string newType)
{
	if(newType == "bool") {type = Type::BOOL; return; }
	if(newType == "int") {type = Type::INT; return; }
	if(newType == "flut") {type = Type::FLUT; return; }
	if(newType == "fita") {type = Type::FITA; return; }

	ThrowInternal("None valid type provided at variable asign (syntree.cpp, line 34)");
}