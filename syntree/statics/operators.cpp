#include "..\..\headers\syntree\operators.h"

Operator::~Operator()
{
	for(unsigned int i = 1; i >= 0; i--)
	{
		if(operands[i]->isAttachedToVariable)
			continue;
		
		delete operands[i];
	}
}

// --------------------------------- / Implementation

LiteralNode* ArithmeticOperator::result()
{
	LiteralNode* literal = new LiteralNode();
	literal->type = Type::INT;
	if(operands[0]->type == Type::FLUT || operands[1]->type == Type::FLUT)
	{
		literal->type = Type::FLUT;
	}

	switch(literal->type)
	{
		case Type::INT:
			literal->value = std::to_string(operands[0]->toInt() + operands[0]->toInt());
			break;
		case Type::FLUT:
			literal->value = std::to_string(operands[0]->toFloat() + operands[0]->toFloat());
			break;
	}

	return literal;
}