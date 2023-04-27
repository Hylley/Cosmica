#ifndef OPERATORS_NODE_H
#define OPERATORS_NODE_H

#include "node.h"
#include "literal.h"

class Operator : public Node
{
	public:
		Node* left;
		Node* right;

		char op;

		virtual LiteralNode* result() {};
		virtual ~Operator();
};

class ArithmeticOperator : public Operator
{
	public:
		LiteralNode* result() override;
};

class ComparisonOperator : public Operator {};
class LogicalOperator    : public Operator {};
class AssignmentOperator : public Operator {};

#endif