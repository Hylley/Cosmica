#include "..\..\headers\syntree\evaluation.h"

void EvaluationNode::Evaluate()
{
	return;
}

EvaluationNode::~EvaluationNode()
{
	unsigned int size = childrenCount();

	for(unsigned int i = size - 1; i >= 0; i--)
	{
		removeChild(i, true);
	}
}

void EvaluationNode::addChild(Node* newChild)
{
	children.push_back(newChild);
	newChild->changeParent(this);
}

Node* EvaluationNode::getChild(unsigned int index)
{
	return children[index];
}

void EvaluationNode::removeChild(unsigned int index, bool del = false)
{
	if(del)
	{
		Node* child = children[index];
		delete child;
	}

	children.erase(children.begin() + index);
}

unsigned int EvaluationNode::childrenCount()
{
	return children.size();
}