#ifndef COMPARISON_NODE_H
#define COMPARISON_NODE_H

#include "node.h"

class ComparisonNode : public Node // Comparison (<, >, >=, != etc)
{
	public:
		char op;
		Node* left;
		Node* right;
};

#endif