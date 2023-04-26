#ifndef LITERAL_NODE_H
#define LITERAL_NODE_H

#include "node.h"
#include <cctype>
#include <typeinfo>

template <typename T>
class LiteralNode : public Node
{
	public:
		bool isAttachedToVariable = false;
		T value;

		Type getType();
};

#endif