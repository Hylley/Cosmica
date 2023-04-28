#ifndef IF_NODE_H
#define IF_NODE_H

#include "node.h"
#include "block.h"

class IfNode : public BlockNode
{
	public:
		virtual void Evaluate() override;
};

#endif