#include "headers/syntree.h"

// Building blocks

class Node
{
	public:
		virtual ~Node() {}
};


class VariableNode : public Node
{
	public:
		std::string name;
};

class LiteralNode : public Node
{
	public:
		enum class Type { BOOL, INT, FLOAT, DOUBLE, CHAR, STRING };
		Type type;
		std::string value;
};

class BlockNode : public Node
{
	public:
		std::string name;
		std::vector<Node*> children;
		std::vector<Node*> functions;

		bool hasVariableInPool(VariableNode* variable)
		{
			return symbolTable.count(variable->name);
		}

		LiteralNode* getVariableInPool(VariableNode* variable)
		{
			return symbolTable[variable->name];
		}
	
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