#include "headers/scanner.h"

bool Fits(std::string& str, std::string model) {
    int i = 0, j = 0, m = str.length(), n = model.length();
    while (i < m && j < n) {
        if (model[j] == '%') {
            // If the % character is the last character in the second string,
            // then the first string must end at this point for the strings to fit
            if (j == n - 1) {
                return true;
            }
            // Otherwise, search for the next non-% character in the second string
            char nextChar = model[j + 1];
            int k = i;
            while (k < m && str[k] != nextChar) {
                k++;
            }
            // If the next non-% character is not found in the first string,
            // then the strings don't fit
            if (k == m) {
                return false;
            }
            i = k + 1;
            j += 2;
        } else {
            // If the current characters in the two strings don't match
            // and the current character in the second string is not a %,
            // the strings don't fit the pattern
            if (str[i] != model[j]) {
                return false;
            }
            i++;
            j++;
        }
    }
    // If we have reached the end of the second string, the strings fit the pattern
    // regardless of the remaining characters in the first string
    if (j == n) {
        return true;
    }
    return false;
}

void ScanLine(std::string& line, BlockNode& parent)
{
	// IF, ELSE, ELSE-IF
	if(Fits(line, "se %:"))
	{
		std::cout << "IF" << std::endl;
		return;
	}else if(Fits(line, "entretanto:"))
	{
		std::cout << "ELSE" << std::endl;
		return;
	}else if(Fits(line, "entretanto, se %:"))
	{
		std::cout << "ELSE-IF" << std::endl;
		return;
	}

	// VARIABLE EQUAL ASIGN
	if(Fits(line, "%==%"))
	{
		std::cout << "EQUAL COMP" << std::endl;

		return;
	}else if(Fits(line, "%=%"))
	{
		std::cout << "EQUAL" << std::endl;
		return;
	}

	//FUNCTION DEFINITION AND CALL
	if(Fits(line, "%(%):"))
	{
		std::cout << "FUNC DEF" << std::endl;

		return;
	}else if(Fits(line, "%(%)"))
	{
		std::cout << "FUNC CALL" << std::endl;
		return;
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