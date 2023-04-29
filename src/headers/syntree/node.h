#ifndef STATIC_NODE_H
#define STATIC_NODE_H

#include <string>
#include <unordered_map>
#include "../../headers/debug.h"

class Node
{
	protected:
		Node* parent;
	
	public:
		virtual ~Node() {}
		void changeParent(Node* newParent);
};

#endif