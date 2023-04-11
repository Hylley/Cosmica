#include "headers/prch.h"
#include "headers/debug.h"
#include "headers/scanner.h"
#include "headers/parser.h"
#include "headers/interpreter.h"
#include "headers/syntree.h"

int	main(int argc, char	*argv[]) {
	if(argc	< 2)
	{
		std::cerr << "No file provided." << std::endl;
		return 1;
	}

	std::string filePath = argv[1];
	std::ifstream file(filePath);

	if (!file.is_open()) {
		std::cerr << "Failed to open path: " << filePath << std::endl;
		return 1;
	}

	std::ostringstream stringStream = std::ostringstream{};
	stringStream << file.rdbuf();
	std::string content = stringStream.str();

	// Instantiate main parent node
	BlockNode parentNode = BlockNode();
	// Pass the raw file to the lexer, it will check for errors
	// and automatically generate the AST into the given node.
	Lexer(content, parentNode, filePath);

	// Execute the code
	Execute(parentNode);

	return 0;
}