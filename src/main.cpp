#include "headers/main.h"
#include "headers/debug.h"
#include "headers/scanner.h"
#include "headers/parser.h"

#include "headers/syntree/block.h"

std::string reserved_keywords[9] =
{
	":",
	"bool",
	"int",
	"flut",
	"fita",
	"se",
	"entretanto",
	"entretanto,"
};

void sigint_handler(int sig)
{
	std::cerr << "KeyboardInterrupt: " << "Interrupção manual (Ctrl + C) ";
	signal(SIGINT, SIG_DFL);
	GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);
	Terminate(1);
}

int main(int argc, char	*argv[])
{
	#if SHOW_PROGRAM_RUN_TIME
	std::cout << "{runtime} init" << std::endl;
	#endif

	SetConsoleOutputCP(65001);
	signal(SIGINT, sigint_handler);

	// ------------------------- Open file
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
	// -------------------------

	BlockNode mainNode = BlockNode(); // Instantiate main parent node
	
	Lexer(content, mainNode, filePath); // Pass the raw file to the lexer, it will check for errors
	// and automatically generate the AST into the given node.

	// Start a chain reaction that execute the whole tree
	mainNode.Evaluate();

	Terminate(0);
}