#include "..\..\headers\syntree\literal.h"

Type LiteralNode::getType()
{
	return type;
}

void LiteralNode::setType(Type newType)
{
	type = newType;
}

std::string LiteralNode::getTypeStr()
{
	if(type == Type::BOOL) { return "bool"; }
	if(type == Type::INT ) { return "int";  }
	if(type == Type::FLUT) { return "flut"; }
	if(type == Type::FITA) { return "fita"; }

	ThrowInternal("Wtf happened here? (literal.cpp, line 20)");
}

void LiteralNode::setTypeStr(std::string newType)
{
	if(newType == "bool") { type = Type::BOOL; return; }
	if(newType == "int" ) { type = Type::INT; return;  }
	if(newType == "flut") { type = Type::FLUT; return; }
	if(newType == "fita") { type = Type::FITA; return; }

	ThrowInternal("No valid type provided at variable asign (syntree.cpp, line 92)");
}

// -----------------------------------/ Convertions

std::string LiteralNode::toString()
{
	return value;
}

int LiteralNode::toInt()
{
	if(type == Type::BOOL)
		return toBool();

	if(!isdigit(value[0]))
		return 0;

	return std::stoi(value);
}

float LiteralNode::toFloat()
{
	if(!isdigit(value[0]))
		return 0.0f;

	return std::stof(value);	
}

bool LiteralNode::toBool()
{
	if(type == Type::BOOL)
	{
		if(value == "falso" || value == "false" || value == "não")
			return false;
		if(value == "verdadeiro" || value == "true" || value == "sim")
			return true;
	}

	return !toString().empty() || toInt() || toFloat();
}