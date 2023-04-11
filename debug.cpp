#include "headers/debug.h"


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

	std::cout << errorName << ": " << details << " at line " << line << " in " << fileName << std::endl;

	exit(1);
}