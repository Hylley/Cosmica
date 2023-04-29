#ifndef LITERAL_NODE_H
#define LITERAL_NODE_H

#include "node.h"
#include <cctype>
#include <typeinfo>
#include <regex>

enum class Type { BOOL, INT, FLUT, FITA, NULO };
extern std::regex inteiro;
extern std::regex fita;
extern std::regex flutuante;
extern std::regex booleano;

class LiteralNode : public Node
{
	public:
		std::string value;
		Type type;
		bool isAttachedToVariable = false;

		Type getType();

		template <typename T>
		T to();
};

Type findDataType(std::string& input);

#endif