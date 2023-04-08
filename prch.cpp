#include "headers/prch.h"

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

	// Create a vector of string vectors calling the "Tokenize" function from the Scanner.
	std::vector<std::vector<std::string>> tokens = Tokenize(content);

	// Check for grammar erros
	int lines = tokens.size();
	for(int i = 0; i < lines; i++)
	{
		
	}

	return 0;
}