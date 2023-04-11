#include "headers/debug.h"

#if DEBUG_DEVELOPER_FEEDBACK
std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
#endif

void ThrowException(ExcepctionType exception, std::string fileName, int line, std::string details)
{
	// Don't judge me. It was either this or use macros.
	std::string errorName;
	switch(exception)
	{
		case RuntimeError:
			errorName = "RuntimeError";
			break;
		case SyntaxError:
			errorName = "SyntaxError";
			break;
		case ValueError:
			errorName = "ValueError";
			break;
		case ZeroDivisionError:
			errorName = "ZeroDivisionError";
			break;
		case KeyboardInterrupt:
			errorName = "KeyboardInterrupt";
			break;
	}

	std::cerr << errorName << ": " << details << ";" << " na linha " << line << " em " << fileName << std::endl;

	Terminate();
	exit(1);
}

void Terminate()
{
	#if DEBUG_DEVELOPER_FEEDBACK
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "RUNTIME: " << duration.count() << " mls" << std::endl;
	#endif

	return;
}