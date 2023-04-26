#ifndef OPERATORS_NODE_H
#define OPERATORS_NODE_H

#include "node.h"
#include "literal.h"

class Operator : Node
{
	public:
		std::vector<LiteralNode<void*>*> operands;

		std::string op;

		virtual LiteralNode<void*>* result() {};
		virtual ~Operator();
};

template <typename T>
class ArithmeticOperator : Operator
{
	public:
		LiteralNode<T>* result() override;
};

class ComparisonOperator : Operator {};
class LogicalOperator    : Operator {};
class AssignmentOperator : Operator {};

#endif