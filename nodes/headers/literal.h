#ifndef LITERAL_NODE_H
#define LITERAL_NODE_H

#include "node.h"

class LiteralNode : public Node
{
	public:
		Type type;
		std::string value;

		void SetType(std::string newType);
};

#endif