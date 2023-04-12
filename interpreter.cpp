#include "headers/interpreter.h"

void Execute(BlockNode& parent)
{
	unsigned int children = parent.children.size();

	for(unsigned int i = 0; i < children; i++)
	{
		VariableNode* child = dynamic_cast<VariableNode*>(parent.children[i]);
		if(child != nullptr)
		{
			std::cout << child->name << std::endl;
		}
	}
}