#include "headers/interpreter.h"

void Execute(BlockNode& parent)
{
	unsigned int children = parent.childrenCount();

	for(unsigned int i = 0; i < children; i++)
	{
		VariablAssign* child = dynamic_cast<VariablAssign*>(parent.getChild(i));
		if(child != nullptr)
		{
			if(parent.hasVariable(child->name))
			{
				parent.changeVariable(child->name, child->literal);
			}
			else
			{
				parent.addVariable(child->name, child->literal);
			}
		}

		delete child;
	}
}