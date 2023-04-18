#ifndef EVAL_NODE_H
#define EVAL_NODE_H

#include "node.h"

class EvaluationNode : public Node
{
	protected:
		std::vector<Node*> children;

	public:
		void addChild(Node* newChild);
		Node* getChild(unsigned int index);
		void removeChild(unsigned int index, bool del);
		unsigned int childrenCount();

		virtual ~EvaluationNode();
		virtual void Evaluate();
};

#endif