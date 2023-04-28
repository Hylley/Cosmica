#ifndef	DEBUG_H
#define	DEBUG_H

#include "main.h"

#define DEBUG_DEVELOPER_FEEDBACK true

#if DEBUG_DEVELOPER_FEEDBACK
	#define SHOW_PROGRAM_RUN_TIME true
	#define DEBUG_SHOW_LINES false
	#define DEBUG_SHOW_VARIABLES_CHANGES false
	#define DEBUG_SHOW_MATH_EXPRESSION_EVAL true
#endif

#if SHOW_PROGRAM_RUN_TIME
#include <chrono>
extern std::chrono::high_resolution_clock::time_point start;
#endif

typedef	enum
{
	RuntimeError, // General error
	SyntaxError,
	ValueError,
	TypeError,
	ZeroDivisionError,
	KeyboardInterrupt,
	InternalError
} ExcepctionType;

void ThrowException(ExcepctionType exception, std::string fileName, int line, std::string details);
void ThrowInternal(std::string details);
void Terminate(int execode);

#endif