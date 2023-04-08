#ifndef	DEBUG_H
#define	DEBUG_H

#include "prch.h"

typedef	enum
{
	RuntimeError, // General error
	SyntaxError,
	ValueError,
	ZeroDivisionError,
	KeyboardInterrupt
} ExcepctionType;

void ThrowException(ExcepctionType exception, std::string fileName, int line, std::string details);

#endif