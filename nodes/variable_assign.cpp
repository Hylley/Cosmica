#include "headers/variable_assign.h"

void VariablAssign::Evaluate()
{
	BlockNode* block = dynamic_cast<BlockNode*>(parent);
	if(block == nullptr)
	{
		ThrowInternal("Variable Asign isn't attached to a valid member (variable_assing.cpp, line 8)");
	}

	if(block->hasVariable(name))
	{
		block->changeVariable(name, literal);
		return;
	}

	block->addVariable(name, literal);
}