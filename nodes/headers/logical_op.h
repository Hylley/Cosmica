#ifndef LOGICAL_OP_NODE_H
#define LOGICAL_OP_NODE_H

#include "node.h"

class LogicalOpNode : public Node // Logic (OR, AND, NOT)
{
	public:
		std::string op;
		std::vector<Node*> operands;
};

#endif