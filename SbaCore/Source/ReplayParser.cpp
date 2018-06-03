#include "ReplayParser.h"
#include "Python.h"

ReplayParser::ReplayParser() {
	Py_Initialize();
}

ReplayParser::~ReplayParser() {
	Py_Finalize();
}

ParseResult ReplayParser::Parse(QString replayPath) {
	return ParseResult(QString("TODO"));
}
