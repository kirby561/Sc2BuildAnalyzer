#include "ReplayParser.h"
#include "Python.h"

ReplayParser::ReplayParser(QString sc2ProtocolPath) {
	_sc2ProtocolPath = sc2ProtocolPath;
	Py_Initialize();
}

ReplayParser::~ReplayParser() {
	Py_Finalize();
}

ParseResult ReplayParser::Parse(QString replayPath) {
	FILE* file = fopen(_sc2ProtocolPath.toStdString().c_str(), "r");
	if (file == nullptr) {
		return ParseResult(QString("Couldn't open the file at ") + replayPath, false);
	}

	// Setup the command line arguments
	const int argc = 2;
	char** argv = new char*[argc];
	std::string s2ProtocolPathStr = _sc2ProtocolPath.toStdString();
	std::string replayPathStr = replayPath.toStdString();
	argv[0] = new char[s2ProtocolPathStr.length() + 1];
	strcpy(argv[0], s2ProtocolPathStr.c_str());

	argv[1] = new char[replayPathStr.length() + 1];
	strcpy(argv[1], replayPathStr.c_str());

	PySys_SetArgv(argc, argv);

	// Note: The following works:
	//PyRun_SimpleString("from time import time,ctime\n"
	//	"print('Today is', ctime(time()))\n");

	// Run the script
	int result = PyRun_SimpleFile(file, "s2_cli.py");

	if (PyErr_Occurred()) {
		PyErr_Print();
		return ParseResult("A python error occurred", false);
	}

	// Clean up
	for (int i = 0; i < argc; i++)
		delete[] argv[i];
	delete[] argv;

	return ParseResult(QString("TODO"));
}
