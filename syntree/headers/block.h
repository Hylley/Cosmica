#ifndef BLOCK_NODE_H
#define BLOCK_NODE_H

#include "node.h"
#include "literal.h"

class BlockNode : public Node
{
	private:
		std::unordered_map<std::string, BlockNode*> functions;
	
	protected:
		std::vector<Node*> children;
		std::unordered_map<std::string, LiteralNode*> symbolTable;

	public:
		virtual void Evaluate() override;

		void addChild(Node* newChild);
		Node* getChild(unsigned int index);
		void removeChild(unsigned int index, bool del);
		unsigned int childrenCount();

		bool hasVariable(std::string variableName);
		LiteralNode* getVariable(std::string variableName);
		void changeVariable(std::string variableName, LiteralNode* newValue, bool ignoreTypeCast);
		void addVariable(std::string variableName, LiteralNode* newValue);
};

#endif