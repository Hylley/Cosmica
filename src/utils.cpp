#include "headers/utils.h"

std::string trim(const std::string& str)
{
    // Find the first non-whitespace character from the beginning
    const auto begin = str.find_first_not_of(" \t\n\r");

    if (begin == std::string::npos) {
        // The string is empty or only contains whitespace
        return "";
    }

    // Find the last non-whitespace character from the end
    const auto end = str.find_last_not_of(" \t\n\r");

    // Return the trimmed string
    return str.substr(begin, end - begin + 1);
}