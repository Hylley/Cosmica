#ifndef LITERAL_NODE_H
#define LITERAL_NODE_H

#include "node.h"
#include <cctype>
#include <typeinfo>

class LiteralNode : public Node
{
	public:
		std::string value;
		Type type;
		bool isAttachedToVariable = false;

		Type getType();

		std::string toString();
		int toInt();
		float toFloat();
		bool toBool();
};

#endif