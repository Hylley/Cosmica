#include "headers/parser.h"

BlockNode GenerateAbstractSyntaxTree(std::vector<std::vector<std::string>> tokens)
{
	unsigned int sizel = tokens.size();
	for(unsigned int i = 0; i < sizel; i++)
	{
		unsigned int sizew = tokens[i].size();
		for(unsigned int j = 0; j < sizew; j++)
		{
			std::cout << tokens[i][j] << std::endl;
		}
	}

	return BlockNode();
}