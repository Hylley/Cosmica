#include "headers/scanner.h"

bool Fits(const std::string& str, const std::string& model) {
    size_t strIndex = 0;
    size_t modelIndex = 0;
    char lastChar = '\0'; // Track the last non-wildcard character in the model

    while (strIndex < str.size() && modelIndex < model.size()) {
        if (model[modelIndex] == '%') {
            modelIndex++;
            while (strIndex < str.size() && modelIndex < model.size() && str[strIndex] != model[modelIndex]) {
                strIndex++;
            }
            if (strIndex == str.size()) {
                return false;
            }
            lastChar = '\0'; // Reset the last non-wildcard character in the model
        }
        else if (str[strIndex] == model[modelIndex]) {
            strIndex++;
            modelIndex++;
            if (model[modelIndex - 1] != '%') {
                lastChar = model[modelIndex - 1];
            }
        }
        else {
            if (lastChar != '\0' && model[modelIndex] != '%') {
                // If the current model character is the same as the last non-wildcard character
                // and there is no matching character in the string, return false
                if (lastChar == model[modelIndex]) {
                    return false;
                }
            }
            return false;
        }
    }

    while (modelIndex < model.size() && model[modelIndex] == '%') {
        modelIndex++;
    }

    return modelIndex == model.size();
}

void ScanLine(std::string& line, BlockNode& parent)
{
	if(Fits(line, "%==%"))
	{
		std::cout << "Funcionou!" << std::endl;
	}
}

std::vector<std::string> Lexer(std::string& raw, BlockNode& parent)
{
	std::istringstream fileStream(raw);
	std::string line;
	bool isMultiCommented = false;
	while(std::getline(fileStream, line))
	{
		ScanLine(line, parent);
	}
}