#ifndef	SYNTREE_H
#define	SYNTREE_H

#include "prch.h"
#include "debug.h"
#include <unordered_map>

enum class Type { BOOL, INT, FLUT, FITA };

// Building blocks

class Node
{
	protected:
		unsigned int nodeType = 0;

		Node* parent;

	public:
		unsigned int getType();
		void changeParent(Node* newParent);

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
	private:
		std::vector<Node*> children;
		std::unordered_map<std::string, Type> args;
		std::unordered_map<std::string, BlockNode*> functions;
		std::unordered_map<std::string, LiteralNode*> symbolTable;

	public:
		void addArg(std::string name, Type type);
		// void removeArg(std::string name);

		void addChild(Node* newChild);
		Node* getChild(unsigned int index);
		void removeChild(unsigned int index, bool del);
		unsigned int childrenCount();

		bool hasVariable(std::string variableName);
		LiteralNode* getVariable(std::string variableName);
		void changeVariable(std::string variableName, LiteralNode* newValue);
		void addVariable(std::string variableName, LiteralNode* newValue);
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
		std::vector<LiteralNode*> variablePool;
};

#endif