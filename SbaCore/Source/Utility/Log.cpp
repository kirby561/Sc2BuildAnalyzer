#include "Log.h"
#include <stdarg.h> 

/**
 * Logs an error.
 * @param error The error to log.
 */
void Log::Error(const char* error, ...) {
	printf("Error: ");
	va_list argptr;
    va_start(argptr, error);
    vfprintf(stdout, error, argptr);
    va_end(argptr);
	printf("\n");
	fflush(stdout);
}

/**
 * Logs an error.
 * @param error The error as a string.
 */
void Log::Error(const std::string& error) {
	std::cout << "Error: " << error.c_str() << std::endl;
}

/**
 * Logs a warning.
 * @param warning The warning to log
 */
void Log::Warn(const char* warning, ...) {
	printf("Warning: ");
	va_list argptr;
    va_start(argptr, warning);
    vfprintf(stdout, warning, argptr);
    va_end(argptr);
	printf("\n");
	fflush(stdout);
}

/**
 * Logs a warning.
 * @param warning The warning as a string.
 */
void Log::Warn(const std::string& warning) {
	std::cout << "Warning: " << warning.c_str() << std::endl;
}

/**
 * Logs a message.
 * @param information The string to log as a message
 */
void Log::Message(const char* information, ...) {
	va_list argptr;
    va_start(argptr, information);
    vfprintf(stdout, information, argptr);
    va_end(argptr);
	printf("\n");
	fflush(stdout);
}

/**
 * Logs a message (information, no cause fo alarm).
 * @param information The message to log as a string.
 */
void Log::Message(const std::string& information) {
	std::cout << information.c_str() << std::endl;
}

void Log::Crash(const char* error, ...) {
	Log::Error(error);

	// TODO: crash gracefully so the debugger catches it.
}

void Log::Crash(const std::string& error) {
	Log::Error(error);

	// TODO: crash gracefully so the debugger catches it.
}
