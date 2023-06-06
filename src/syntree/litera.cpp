#include "literal.hpp"

std::regex inteiro("^[0-9]+$");
std::regex fita("(.*)((\'(.*)\n*(.*)\')|(\"(.*)\n*(.*)\"))([ ]*)");
std::regex flutuante("^([0-9+]|[0-9]*[.][0-9]+)f?$");
std::regex booleano("^verdadeiro|falso|sim|não$");

Type Literal::getType()
{
	return type;
}

Type findDataType(std::string& value)
{
	if(std::regex_match(value, booleano))
		return Type::BOOL;
		
	if(std::regex_match(value, inteiro))
		return Type::INT;
	
	if(std::regex_match(value, flutuante))
		return Type::FLUT;
	
	if(std::regex_match(value, fita))
		return Type::FITA;
	
	return Type::NULO;
}

template <>
std::string Literal::to<std::string>()
{
	return value;
}

template <>
int Literal::to<int>()
{
	if(type == Type::FITA)
		ThrowException(ValueError, file, line, "Cannot convert FITA to INT");

	if(!isdigit(value[0]))
		return 0;

	return std::stoi(value);
}

template <>
float Literal::to<float>()
{
	if(type == Type::FITA)
		ThrowInternal("Cannot convert FITA to FLUT");

	if(!isdigit(value[0]))
		return 0.0f;

	return std::stof(value);	
}

template <>
bool Literal::to<bool>()
{
	return (bool)(!to<std::string>().empty() || to<int>() || to<float>());
}