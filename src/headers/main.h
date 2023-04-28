#ifndef COSMICA_H
#define COSMICA_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <windows.h>
#include <signal.h>


extern std::string reserved_keywords[9];
void sigint_handler(int sig);
std::string openFile(std::string filePath);

#endif