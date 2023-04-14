#ifndef BINARY_OP_NODE_H
#define BINARY_OP_NODE_H

#include "node.h"

class BinaryOpNode : public Node // Math (x + y, x * z)
{
	public:
		char op;
		Node* left;
		Node* right;
};

#endif