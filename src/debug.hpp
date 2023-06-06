#pragma once

#include <iostream>
#include <unordered_map>
#include <string>

#define DEBUG_DEVELOPER_FEEDBACK true
#if DEBUG_DEVELOPER_FEEDBACK
	#define SHOW_PROGRAM_RUN_TIME true
	#define SHOW_PROGRAM_EXECUTION_PROCESS false
	#define SHOW_LINES_PARSING true
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