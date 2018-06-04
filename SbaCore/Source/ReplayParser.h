#pragma once

#include <QString>
#include <stdio.h>
#include "Log.h"

class ParseResult {
public:
	ParseResult(QString replayJson) {
		_replayJson = replayJson;
		_succeeded = true;
	}

	ParseResult(QString errorDetails, bool succeeded) {
		if (succeeded) {
			Log::Error("This constructor should only be used for parse errors.");
			std::abort();
		}
		_succeeded = false;
		_errorDetails = errorDetails;
	}

	QString GetErrorDetails() { return _errorDetails; }
	QString GetReplayJson() { return _replayJson; }

	bool Succeeded() { return _succeeded; }

private:
	QString _replayJson;
	QString _errorDetails;
	bool _succeeded = false;
};

/**
 * This uses a Python interpreter to parse the replay file so there should only
 *		really be one of these at a time.
 **/
class ReplayParser {
public:
	ReplayParser();
	virtual ~ReplayParser();

	ParseResult Parse(QString replayPath);
};

