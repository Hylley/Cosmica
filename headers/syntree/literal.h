#ifndef LITERAL_NODE_H
#define LITERAL_NODE_H

#include "node.h"
#include <cctype>

class LiteralNode : public Node
{
	public:
		Type type;
		bool isAttachedToVariable = false;
		std::string value;

		Type getType();
		void setType(Type newType);
		std::string getTypeStr();
		void setTypeStr(std::string newType);

		std::string toString();
		int toInt();
		float toFloat();
		bool toBool();
};

#endif