#include "debug.hpp"

#if DEBUG_DEVELOPER_FEEDBACK and SHOW_PROGRAM_RUN_TIME
#include <chrono>
std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
#endif

std::unordered_map<ExcepctionType, std::string> expection_string =
{
	{RuntimeError, "RuntimeError"},
	{SyntaxError, "SyntaxError"},
	{ValueError, "ValueError"},
	{TypeError, "TypeError"},
	{ZeroDivisionError, "ZeroDivisionError"},
	{KeyboardInterrupt, "KeyboardInterrupt"},
	{InternalError, "InternalError"}
};

void ThrowInternal(std::string details)
{
	std::cerr << "InternalError: " << details << std::endl;
	Terminate(1);
}

void ThrowException(ExcepctionType exception, std::string fileName, int line, std::string details)
{
	// Do not judge me. It was either this or use macros.
	std::string errorName = expection_string[exception];

	std::cerr << errorName << ": " << details << ";" << " na linha " << line << " em " << fileName << std::endl;

	Terminate(1);
}

void Terminate(int execode = 0)
{
	#if SHOW_PROGRAM_RUN_TIME
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "{runtime} duration: " << duration.count() << " mls" << std::endl;
	#endif

	exit(execode);
}