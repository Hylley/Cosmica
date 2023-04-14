#ifndef NODE_H
#define NODE_H

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
		virtual void Evaluate();
		void changeParent(Node* newParent);
};

#endif