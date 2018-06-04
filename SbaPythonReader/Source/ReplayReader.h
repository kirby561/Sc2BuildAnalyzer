#pragma once

#include <QString>

class ReplayReader {
public:
	enum ReadResult {
		Success = 0,
		CouldNotOpenFile = -1000,
		ScriptError = -1001
	};

	ReplayReader(QString sc2ProtocolPath);
	virtual ~ReplayReader();

	int Read(int argCount, char** args);
	
private:
	QString _sc2ProtocolPath;

};

