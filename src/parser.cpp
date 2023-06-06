#include "parser.hpp"

#pragma region regex definition
std::regex invisibles("^[ \t\n]*$");
std::regex tabs("^(\t*[ ]*)(.*)");
std::regex single_line_comment("(.*)--.*");
std::regex multi_line_comment[3] =
{
	std::regex ("(.*)--\\[\\[.*"), // Open comment
	std::regex (".*\\]\\]"), // Close comment
	std::regex (".*\\]\\].+") // Incorrect comment
};
#pragma endregion

Node* Parse(std::string& line, int tab_level, std::unordered_map<unsigned int, Block*>& tab_table, std::string& file_name, int& line_number)
{
	#if SHOW_LINES_PARSING
	std::cout << "{ " << line <<" }" << std::endl;
	#endif

	std::smatch matches;

	if(line.empty() || std::regex_match(line, matches, invisibles))
		return nullptr;
	
	ThrowException(SyntaxError, file_name, line_number, "Impossível resolver: \"" + line + "\"");
}