#include "headers/interpreter.h"

void Execute(BlockNode& parent)
{
	unsigned int children = parent.children.size();

	for(unsigned int i = 0; i < children; i++)
	{
		VariablAssign* child = dynamic_cast<VariablAssign*>(parent.children[i]);
		if(child != nullptr)
		{
			if(parent.hasVariableInPool(child->name))
			{
				parent.changeVariableInPool(child->name, child->literal);
			}
			else
			{
				parent.addVariableInPool(child->name, child->literal);
			}
		}

		delete child;
	}

	#if DEBUG_SHOW_GLOBAL_VARIABLES
	std::cout << "{" << std::endl;
	for (const auto& pair : parent.symbolTable) {
		switch(pair.second->type)
		{
			case Type::BOOL:
				std::cout << "\t(bool) ";
				break;
			case Type::INT:
				std::cout << "\t(int) ";
				break;
			case Type::FLUT:
				std::cout << "\t(flut) ";
				break;
			case Type::FITA:
				std::cout << "\t(fita) ";
				break;
		}
		std::cout << pair.first << ": " << pair.second->value << std::endl;
	}
	std::cout << "}" << std::endl;
	#endif
}