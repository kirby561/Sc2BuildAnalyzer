#include "ReplayParser.h"
#include <QProcess>
#include <QStringList>
#include <QCoreApplication>

ReplayParser::ReplayParser() {
}

ReplayParser::~ReplayParser() {
}

ParseResult ReplayParser::Parse(QString replayPath) {
	QProcess parsingProcess;
	QString program(QCoreApplication::applicationDirPath() + "/SbaPythonReader.exe");
	QStringList arguments;
	arguments.append(replayPath);
	arguments.append("--gameevents"); // ?? TODO: Provide different options for what data to get or get all of it
	arguments.append("--json");
	parsingProcess.start(program, arguments);
	parsingProcess.waitForFinished();
	QString output(parsingProcess.readAllStandardOutput());
	QString errors(parsingProcess.readAllStandardError());
	int returnCode = parsingProcess.exitCode();

	if (returnCode != 0) {
		return ParseResult(QString("An error occurred.  Code: ") + returnCode + QString(" Output: ") + output + QString(" Errors: ") + errors, false);
	}
	return ParseResult(output);
}
