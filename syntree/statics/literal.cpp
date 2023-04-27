#include "..\..\headers\syntree\literal.h"

Type LiteralNode::getType()
{
	return type;
}

// -----------------------------------/ Convertions

template <>
std::string LiteralNode::to<std::string>()
{
	return value;
}

template <>
int LiteralNode::to<int>()
{
	if(type == Type::FITA)
		ThrowInternal("Cannot convert FITA to INT");

	if(type == Type::BOOL)
	{
		if(value == "falso" || value == "false" || value == "não")
			return 0;
		if(value == "verdadeiro" || value == "true" || value == "sim")
			return 1;
	}

	if(!isdigit(value[0]))
		return 0;

	return std::stoi(value);
}

template <>
float LiteralNode::to<float>()
{
	if(type == Type::FITA)
		ThrowInternal("Cannot convert FITA to FLUT");

	if(!isdigit(value[0]))
		return 0.0f;

	return std::stof(value);	
}

template <>
bool LiteralNode::to<bool>()
{
	if(type == Type::BOOL)
	{
		if(value == "falso" || value == "false" || value == "não")
			return false;
		if(value == "verdadeiro" || value == "true" || value == "sim")
			return true;
	}

	return (bool)(!to<std::string>().empty() || to<int>() || to<float>());
}