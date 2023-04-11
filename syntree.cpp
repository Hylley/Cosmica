#include "headers/syntree.h"

bool BlockNode::hasVariableInPool(VariableNode* variable)
{
	return symbolTable.count(variable->name);
}

LiteralNode* BlockNode::getVariableInPool(VariableNode* variable)
{
	return symbolTable[variable->name];
}

void LiteralNode::SetType(std::string newType)
{
	if(newType == "bool") {type = Type::BOOL; return; }
	if(newType == "int") {type = Type::INT; return; }
	if(newType == "flut") {type = Type::FLUT; return; }
	if(newType == "fita") {type = Type::FITA; return; }

	ThrowInternal("None valid type provided at variable asign (syntree.cpp, line 20)");
}