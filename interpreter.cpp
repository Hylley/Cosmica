#include "headers/interpreter.h"

void Execute(BlockNode& parent)
{
	unsigned int children = parent.childrenCount();

	for(unsigned int i = 0; i < children; i++)
	{
		Node* child = parent.getChild(i);

		child->Evaluate();

		delete child;
	}
}