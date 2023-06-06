#include "scanner.hpp"

int spaces_equivalent_to_tab = 4;

void Scan(std::string& line, bool& is_multi_line_commented, int& tab_level, std::string& filtered_line, std::string& file_name, int& line_number)
{
	std::smatch matches;

	#pragma region handle comments
	if(!is_multi_line_commented)
	{
		// If is an valid multi comment openning
		if(std::regex_match(line, matches, multiLineComment[0]))
		{
			line = matches[1];
			is_multi_line_commented = true;
		}
		// If is an valid single line comment openning
		else if(std::regex_match(line, matches, singleLineComment))
		{
			line = matches[1];
		}
	}
	else
	{
		if(std::regex_match(line, multiLineComment[2]))
			ThrowException(SyntaxError, file_name, line_number, "Fechamento de comentário precisa de linha exclusiva");

		if(std::regex_match(line, matches, multiLineComment[1]))
		{
			line = matches[1];
			is_multi_line_commented = false;
		}

		if(is_multi_line_commented)
			return;
	}

	if(line.empty() || std::regex_match(line, matches, invisibles))
		return;
	#pragma endregion

	#pragma region handle identation
	std::regex_match(line, matches, tabs);
	std::string ident = matches[1];
	int tabs = 0;
	int spaces = 0;

	for(int i = 0; i < ident.length(); i++)
	{
		if(ident[i] == '\t')
		{
			tabs++;
			continue;
		}

		if(ident[i] == ' ')
		{
			if(spaces < spaces_equivalent_to_tab - 1)
			{
				spaces++;
				continue;
			}

			spaces = 0;
			tabs++;
		}
	}

	if(spaces != 0)
		ThrowException(SyntaxError, file_name, line_number, "Uso inconsistente de tabs e espaços");

	tab_level = tabs;
	filtered_line = matches[2];
	#pragma endregion
}