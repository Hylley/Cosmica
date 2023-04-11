#ifndef	DEBUG_H
#define	DEBUG_H

#include "prch.h"

#define DEBUG_DEVELOPER_FEEDBACK true
#define DEBUG_SHOW_LINES false

#if DEBUG_DEVELOPER_FEEDBACK
#include <chrono>
extern std::chrono::high_resolution_clock::time_point start;
#endif

typedef	enum
{
	RuntimeError, // General error
	SyntaxError,
	ValueError,
	ZeroDivisionError,
	KeyboardInterrupt
} ExcepctionType;

void ThrowException(ExcepctionType exception, std::string fileName, int line, std::string details);
void Terminate();

#endif