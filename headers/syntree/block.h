#ifndef BLOCK_NODE_H
#define BLOCK_NODE_H

#include "evaluation.h"
#include "literal.h"

class BlockNode : public EvaluationNode
{
	private:
		std::unordered_map<std::string, BlockNode*> functions;
	
	protected:
		std::unordered_map<std::string, LiteralNode*> symbolTable;

	public:
		virtual void Evaluate() override;

		bool hasVariable(std::string variableName);
		LiteralNode* getVariable(std::string variableName);
		void changeVariable(std::string variableName, LiteralNode* newValue, bool ignoreTypeCast);
		void addVariable(std::string variableName, LiteralNode* newValue);
};

#endif