#include "node.hpp"

Node::~Node()
{
	unsigned int size = children.size();

	for(unsigned int i = size - 1; i >= 0; i--)
	{
		removeChild(i, true);
	}
}

void Node::removeChild(unsigned int index, bool del = false)
{
	if(del)
	{
		Node* child = children[index];
		delete child;
	}

	children.erase(children.begin() + index);
}

void Node::addChild(Node* child)
{
	children.push_back(child);
	child->parent = this;
}