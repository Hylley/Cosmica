#include "..\..\headers\syntree\operators.h"

Operator::~Operator()
{
	if(LiteralNode* any = dynamic_cast<LiteralNode*>(left))
	{
		if(!any->isAttachedToVariable)
		{
			delete left;
		}
	}else
	{
		delete left;
	}

	if(LiteralNode* any = dynamic_cast<LiteralNode*>(right))
	{
		if(!any->isAttachedToVariable)
		{
			delete right;
		}
	}else
	{
		delete right;
	}
}

// --------------------------------- / Implementation

LiteralNode* ArithmeticOperator::result()
{
	LiteralNode* leftOperand = nullptr;
	LiteralNode* rightOperand = nullptr;


	if(LiteralNode* any = dynamic_cast<LiteralNode*>(left))
	{
		leftOperand = any;
	}
	else if(Operator* any = dynamic_cast<Operator*>(left))
	{
		leftOperand = any->result();
	}
	else
	{
		ThrowInternal("Arithmetic operation failed (operators.cpp : result");
	}

	if(LiteralNode* any = dynamic_cast<LiteralNode*>(right))
	{
		rightOperand = any;
	}
	else if(Operator* any = dynamic_cast<Operator*>(right))
	{
		rightOperand = any->result();
	}
	else
	{
		ThrowInternal("Arithmetic operation failed (operators.cpp : result");
	}

	LiteralNode* literal = new LiteralNode();
	literal->type = Type::INT;
	if(leftOperand->type == Type::FLUT || rightOperand->type == Type::FLUT)
	{
		literal->type = Type::FLUT;
	}

	switch(literal->type)
	{
		case Type::INT:
			literal->value = std::to_string(leftOperand->toInt() + rightOperand->toInt());
			break;
		case Type::FLUT:
			literal->value = std::to_string(rightOperand->toFloat() + rightOperand->toFloat());
			break;
	}

	return literal;
}