#include "headers/literal.h"

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