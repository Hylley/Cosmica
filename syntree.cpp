#include "headers/syntree.h"

bool BlockNode::hasVariableInPool(VariableNode* variable)
{
	return symbolTable.count(variable->name);
}

LiteralNode* BlockNode::getVariableInPool(VariableNode* variable)
{
	return symbolTable[variable->name];
}