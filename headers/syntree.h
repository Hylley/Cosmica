#ifndef	SYNTREE_H
#define	SYNTREE_H

#include "prch.h"
#include "debug.h"
#include <unordered_map>

enum class Type { BOOL, INT, FLUT, FITA };

// Building blocks

class Node
{
	public:
		virtual ~Node() {}
};

class LiteralNode : public Node
{
	public:
		Type type;
		std::string value;

		void SetType(std::string newType);
};

class VariablAssign : public Node
{
	public:
		std::string name;
		LiteralNode* literal;
};

class BlockNode : public Node
{
	public:
		std::string name;
		std::vector<Node*> children;
		std::vector<Node*> functions;
		std::unordered_map<std::string, LiteralNode*> symbolTable;

		bool hasVariableInPool(std::string variableName);
		LiteralNode* getVariableInPool(std::string variableName);
		void changeVariableInPool(std::string variableName, LiteralNode* newValue);
		void addVariableInPool(std::string variableName, LiteralNode* newValue);

		BlockNode() : name("§"), children(std::vector<Node*>()), functions(std::vector<Node*>()) {}

};

// Basic Operations

class BinaryOpNode : public Node // Math (x + y, x * z)
{
	public:
		char op;
		Node* left;
		Node* right;
};

class LogicalOpNode : public Node // Logic (OR, AND, NOT)
{
	public:
		std::string op;
		std::vector<Node*> operands;
};

class ComparisonNode : public Node // Comparison (<, >, >=, != etc)
{
	public:
		char op;
		Node* left;
		Node* right;
};

// A little more complex

class FunctionCallNode : public Node
{
	public:
		std::string name;
		std::vector<Node*> args;
};

#endif