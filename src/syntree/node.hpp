#pragma once

#include <string>
#include <vector>

class Node
{
	public:
		Node* parent;
		std::vector<Node*> children;
		
		std::string file;
		int line;

		virtual ~Node();
		void addChild(Node* child);
		void removeChild(unsigned int index, bool del);
};