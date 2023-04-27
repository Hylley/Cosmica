#include "..\..\headers\syntree\literal.h"

Type LiteralNode::getType()
{
	return type;
}

// -----------------------------------/ Convertions

std::string LiteralNode::toString()
{
	return value;
}

int LiteralNode::toInt()
{
	if(type == Type::FITA)
		ThrowInternal("Cannot convert FITA to INT");

	if(type == Type::BOOL)
		return toBool();

	if(!isdigit(value[0]))
		return 0;

	return std::stoi(value);
}

float LiteralNode::toFloat()
{
	if(type == Type::FITA)
		ThrowInternal("Cannot convert FITA to FLUT");

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