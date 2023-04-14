#ifndef LITERAL_NODE_H
#define LITERAL_NODE_H

#include "node.h"
#include "static_node.h"

class LiteralNode : public StaticNode
{
	private:
		Type type;
	
	public:
		std::string value;

		Type getType();
		void setType(Type newType);
		std::string getTypeStr();
		void setTypeStr(std::string newType);
};

#endif