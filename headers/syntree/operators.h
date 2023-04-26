#ifndef OPERATORS_NODE_H
#define OPERATORS_NODE_H

#include "node.h"
#include "literal.h"

class Operator : Node
{
	public:
		std::vector<LiteralNode*> operands;

		std::string op;

		virtual LiteralNode* result() {};
		virtual ~Operator();
};

class ArithmeticOperator : Operator
{
	public:
		LiteralNode* result() override;
};

class ComparisonOperator : Operator {};
class LogicalOperator    : Operator {};
class AssignmentOperator : Operator {};

#endif