#pragma once

#include <QString>

/**
 * This class runs tests on the various Utility classes
 *    and indicates if they succeeded.
 **/
class UtilityTester {
public:
	/**
	 * Runs the tests and indicates if they passed or not.  Use GetLog() to see why a test failed.
	 * @return Returns true if they succeeded, false otherwise.
	 **/
	bool RunTests();

	/**
	 * @return Returns the log for the last RunTests().  The log contains information about what tests failed and why.
	 **/
	QString GetLog() { return _log; }

private:
	QString _log;

	// Individual tests
	bool TestDataObject();

	// Logging methods
	void Log(QString message);
};
