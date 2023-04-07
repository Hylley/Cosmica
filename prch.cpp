#include "headers/prch.h"

int main() {
    std::string str = "The quick brown fox jumps over the lazy dog";
    std::istringstream iss(str);
    std::string token;
    while (std::getline(iss, token, ' ')) {
        std::cout << token << std::endl;
    }
    return 0;
}