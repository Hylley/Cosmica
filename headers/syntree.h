#ifndef	SYNTREE_H
#define	SYNTREE_H

#include "prch.h"
#include <unordered_map>

// Building blocks

class Node
{
	public:
		virtual ~Node() {}
};

class LiteralNode : public Node
{
	public:
		enum class Type { BOOL, INT, FLUT, CADEIA };
		Type type;
		std::string value;
};

class VariableNode : public Node
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

		bool hasVariableInPool(VariableNode* variable);
		LiteralNode* getVariableInPool(VariableNode* variable);

		BlockNode() : name("§"), children(std::vector<Node*>()), functions(std::vector<Node*>()) {}

	private:
		std::unordered_map<std::string, LiteralNode*> symbolTable;
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