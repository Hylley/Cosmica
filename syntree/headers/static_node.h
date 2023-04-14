#ifndef STATIC_NODE_H
#define STATIC_NODE_H

#include "node.h"
#include "../../headers/debug.h"

class StaticNode
{
	protected:
		Node* parent;

	public:
		virtual ~StaticNode() {}
		void changeParent(Node* newParent);
};

#endif