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
	"porém",
	"porém,"
};

int main(int argc, char *argv[])
{
	if(argc	< 2)
		ThrowInternal("Argumentos insuficientes.");

	#if SHOW_PROGRAM_RUN_TIME
	std::cout << "{runtime} init" << std::endl;
	#endif

	SetConsoleOutputCP(65001);
	signal(SIGINT, sigint_handler);

	std::string filePath = argv[1];
	std::string fileContent = openFile(filePath);

	// Instantiate main parent node;
	BlockNode mainNode = BlockNode();
	// Pass the raw file to the lexer, it will check for errors
	// and automatically generate the AST into the given node;
	Lexer(fileContent, mainNode, filePath);

	// Start a chain reaction that execute the whole tree;
	mainNode.Evaluate();

	// Terminate the program.
	Terminate(0);
}

std::string openFile(std::string filePath)
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

void sigint_handler(int sig)
{
	std::cerr << "KeyboardInterrupt: " << "Interrupção manual (Ctrl + C) ";
	signal(SIGINT, SIG_DFL);
	GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0);
	Terminate(1);
}