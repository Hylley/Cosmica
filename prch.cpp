#include "headers/prch.h"
#include "headers/debug.h"
#include "headers/scanner.h"
#include "headers/parser.h"
#include "headers/interpreter.h"
#include "headers/syntree.h"

std::string reserved_keywords[9] =
{
	":",
	"bool",
	"int",
	"flut",
	"fita",
	"se",
	"entretanto",
	"entretanto,",
	"entretanto, "
};

void sigint_handler(int sig)
{
	Terminate();
	std::cerr << "KeyboardInterrupt: " << "Interrupção manual (Ctrl + C) ";
    signal(SIGINT, SIG_DFL);
    GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);
}

int main(int argc, char	*argv[]) {
	#if DEBUG_DEVELOPER_FEEDBACK
	std::cout << "INIT" << std::endl;
	#endif

	SetConsoleOutputCP(65001);
	signal(SIGINT, sigint_handler);

	if(argc	< 2)
	{
		std::cerr << "Nenhum arquivo providenciado." << std::endl;
		return 1;
	}

	std::string filePath = argv[1];
	std::ifstream file(filePath);

	if (!file.is_open()) {
		std::cerr << "Falha ao abrir caminho: " << filePath << std::endl;
		return 1;
	}

	std::ostringstream stringStream = std::ostringstream{};
	stringStream << file.rdbuf();
	std::string content = stringStream.str();
	file.close();

	// Instantiate main parent node
	BlockNode parentNode = BlockNode();
	// Pass the raw file to the lexer, it will check for errors
	// and automatically generate the AST into the given node.
	Lexer(content, parentNode, filePath);
	// Execute the code
	Execute(parentNode);

	Terminate();
	return 0;
}