#include "headers/prch.h"

int	main(int argc, char	*argv[]) {
	if(argc	< 2)
	{
		std::cerr << "No file provided." << std::endl;
		return 1;
	}

	std::string filePath = argv[1];
	std::ifstream input(filePath);

	if (!input.is_open()) {
		std::cerr << "Failed to open path: " << filePath << std::endl;
		return 1;
	}

	auto ss = std::ostringstream{};
	std::ifstream input_file(filePath);
	ss << input_file.rdbuf();
	std::string content = ss.str();

	std::vector<std::vector<std::string>> tokens = GetTokens(content);
	int linesVectorSize = tokens.size();
	
	for(int i = 0; i < linesVectorSize; i++)
	{
		int lineVectorSize = tokens[i].size();
		for(int j = 0; j < lineVectorSize; j++)
		{
			std::cout << tokens[i][j] << std::endl;
		}
	}

	return 0;
}