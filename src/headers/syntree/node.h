#ifndef STATIC_NODE_H
#define STATIC_NODE_H

#include <string>
#include <unordered_map>
#include "../../headers/debug.h"

enum class Type { BOOL, INT, FLUT, FITA };

class Node
{
	protected:
		Node* parent;
	
	public:
		virtual ~Node() {}
		void changeParent(Node* newParent);
};

#endif