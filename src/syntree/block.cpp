#include "block.hpp"

void Block::Evaluate()
{
	unsigned int size = children.size();

	for(unsigned int i = 0; i < size; i++)
	{
		Node* child = children[i];
		if(Evaluable* eval = dynamic_cast<Evaluable*>(child))
			eval->Evaluate();

		delete child;
	}
}
