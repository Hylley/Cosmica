#ifndef LITERAL_NODE_H
#define LITERAL_NODE_H

#include "node.h"
#include "static_node.h"

class LiteralNode : public StaticNode
{
	public:
		Type type;
		std::string value;

		void setType(std::string newType);
};

#endif