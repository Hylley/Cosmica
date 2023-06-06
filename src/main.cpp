#include "main.hpp"
#include "debug.hpp"
#include "scanner.hpp"
#include "parser.hpp"

#include "syntree/block.hpp"

std::string reserved_keywords[9] =
{
	":",
	"bool",
	"int",
	"flut",
	"fita",
	"se",
	"porém",
	"porém,"
};

void sigint_handler(int sig)
{
	/*
		In some Unix-like operating systems, including Linux, the SIGINT signal
		is sent to a process when the user interrupts it using the keyboard
		combination Ctrl+C. By default, this signal terminates the process. This
		function handle this situation by, well, terminating the process. For
		more info, check "startup" region.
	*/
	std::cerr << "KeyboardInterrupt: " << "Interrupção manual (Ctrl + C)" << std::endl;
	signal(SIGINT, SIG_DFL);
	GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);

	Terminate(1);
}

std::string open_file(std::string filePath)
{
	std::ifstream file(filePath);

	if (!file.is_open())
		ThrowInternal("Falha ao abrir caminho: " + filePath);

	std::ostringstream stringStream = std::ostringstream{};
	stringStream << file.rdbuf();
	std::string content = stringStream.str();
	file.close();

	return content;
}

int main(int argc, char *argv[])
{
	#pragma region startup
	if(argc	< 2)
		ThrowInternal("Argumentos insuficientes.");

	#if SHOW_PROGRAM_RUN_TIME
	std::cout << "{runtime} init" << std::endl;
	#endif

	// Sets the active code page of the console output to UTF-8 encoding.
	SetConsoleOutputCP(65001);
	// Sets up the signal handler for the SIGINT signal.
	signal(SIGINT, sigint_handler);

	std::string file_path = argv[1];
	std::string file_content = open_file(file_path);
	#pragma endregion

	#pragma region pre-execution
	std::istringstream fileStream(file_content);
	std::string	line;

	Block topNode = Block();
	std::unordered_map<unsigned int, Block*> tab_table =
	{
		{0, &topNode}
	};
	bool is_multi_line_commented =	false;
	int	line_count = 0;
	#pragma endregion

	#pragma region execution
	while(std::getline(fileStream, line))
	{
		std::string filtered_line;
		int tab_level = 0;

		line_count++;

		/*
			Scanning part ->

			The scanner function will filter the current line (remove comments,
			remove tabs and etc).
		*/
		Scan(line, is_multi_line_commented, tab_level, filtered_line, file_path, line_count);

		// if(is_single_line_commented || is_multi_line_commented)
		// {
		// 	if(is_single_line_commented)
		// 		is_single_line_commented = false;
			
		// 	continue;
		// }
		
		/*
			Parsing part ->

			The parsing part will check the syntax and create a syntatic tree
			of it thourgh recursion.
		*/
		Node* object = Parse(filtered_line, tab_level, file_path, line_count);
		if(object != nullptr)
			tab_table[tab_level]->addChild(object);
	}

	/*
		Execution part ->

		The execution part calls the "Evaluate" method, starting a domino
		effect that executes the whole syntatic tree.
	*/
	topNode.Evaluate();
	#pragma endregion

	Terminate(0);
}