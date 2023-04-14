#include "headers/literal.h"

void LiteralNode::setType(std::string newType)
{
	if(newType == "bool") { type = Type::BOOL; return; }
	if(newType == "int" ) { type = Type::INT; return;  }
	if(newType == "flut") { type = Type::FLUT; return; }
	if(newType == "fita") { type = Type::FITA; return; }

	ThrowInternal("No valid type provided at variable asign (syntree.cpp, line 92)");
}