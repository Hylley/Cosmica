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

template <typename T>
std::string calc(LiteralNode* leftOperand, LiteralNode* rightOperand, char op)
{
	switch(op)
	{
		case '+':
				return std::to_string(leftOperand->to<T>() + rightOperand->to<T>());
			break;
		case '-':
				return std::to_string(leftOperand->to<T>() - rightOperand->to<T>());
			break;
		case '*':
				return std::to_string(leftOperand->to<T>() * rightOperand->to<T>());
			break;
		case '/':
				return std::to_string(leftOperand->to<T>() / rightOperand->to<T>());
			break;
		case '%':
				if(leftOperand->type != Type::FLUT || rightOperand->type != Type::FLUT)
					ThrowInternal("Cannot perform modulus with FLUT");
				
				return std::to_string(leftOperand->to<int>() / rightOperand->to<int>());
			break;
	}
}

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

	if(leftOperand->type == Type::FLUT || rightOperand->type == Type::FLUT)
	{
		literal->type = Type::FLUT;
		literal->value = calc<float>(leftOperand, rightOperand, op);
	}else
	{
		literal->type = Type::FLUT;
		literal->value = calc<int>(leftOperand, rightOperand, op);
	}

	return literal;
}