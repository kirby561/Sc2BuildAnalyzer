#pragma once

#include <QString>
#include <QJsonObject>
#include <stdio.h>
#include "Log.h"
#include "ReplayData/Sc2Replay.h"

/**
 * Contains the parsed replay or an error if an error occurred.
 * The caller is responsible for cleaning up the Sc2Replay that is created on Success.
 **/
class ReplayParseResult {
public:
	ReplayParseResult(Sc2Replay* replay) {
		_replay = replay;
		_succeeded = true;
	}

	ReplayParseResult(QString errorDetails, bool succeeded) {
		if (succeeded) {
			Log::Error("This constructor should only be used for parse errors.");
			std::abort();
		}
		_succeeded = false;
		_errorDetails = errorDetails;
	}

	QString GetErrorDetails() { return _errorDetails; }
	Sc2Replay* GetReplay() { return _replay; }

	bool Succeeded() { return _succeeded; }

private:
	Sc2Replay* _replay = nullptr;
	QString _errorDetails;
	bool _succeeded = false;
};

/**
 * This uses a Python interpreter to parse replay files into an Sc2Replay.
 **/
class ReplayParser {
public:
	ReplayParser();
	virtual ~ReplayParser();

	ReplayParseResult Parse(QString replayPath);

private:
	int64_t GetInt64FromJson(QString key, QJsonObject obj);
	QString GetStringFromJson(QString key, QJsonObject obj);
};

