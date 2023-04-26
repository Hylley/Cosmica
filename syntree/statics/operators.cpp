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

template <typename T>
LiteralNode<T>* ArithmeticOperator<T>::result()
{
	T result;

	switch(op)
	{
		case '+':
			result = operands[0]->value + operands[1]->value;
			break;
		case '-':
			result = operands[0]->value - operands[1]->value;
			break;
		case '*':
			result = operands[0]->value * operands[1]->value;
			break;
		case '/':
			result = operands[0]->value / operands[1]->value;
			break;
	}

	LiteralNode<T>* literal = new LiteralNode<T>();
	literal->value = result;

	return literal;
}