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

	/* The "Tokenize" function return a vector for each line in the file
	containing the tokens respective to each one. */
	std::vector<std::vector<std::string>> linesVector = Tokenize(content);

	

	// Abstract Syntax Tree


	return 0;
}