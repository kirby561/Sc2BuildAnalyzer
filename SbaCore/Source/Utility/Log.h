#pragma once

#include <iostream>

/**
 * The Log class is responsible for logging messages,
 *    errors, and warnings that are thrown throughout the
 *    application.
 */
class Log
{
public:
	static void Error(const char* error, ...);
	static void Error(const std::string& error);

	static void Warn(const char* warning, ...);
	static void Warn(const std::string& warning);

	static void Message(const char* information, ...);
	static void Message(const std::string& information);

	static void Crash(const char* error, ...);
	static void Crash(const std::string& error);
};

