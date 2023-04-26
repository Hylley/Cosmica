#include "..\..\headers\syntree\operators.h"

Operator::~Operator()
{
	unsigned int operandsCount = operands.size();

	for(unsigned int i = operandsCount - 1; i >= 0; i--)
	{
		if(operands[i]->isAttachedToVariable)
			continue;
		
		LiteralNode* literal = operands[i];
		operands.erase(operands.begin() + i);
		delete literal;

		if(operands.empty())
        	break;
	}
}

// --------------------------------- / Implementation

LiteralNode* ArithmeticOperator::result()
{
	std::string result;
	Type operationType = Type::INT;

	for(LiteralNode* operand : operands)
	{
		if(operand->type == Type::FITA)
			ThrowInternal("Impossible to do math with FITA");
		if(operand->type == Type::FLUT)
			operationType = Type::FLUT;
	}



}