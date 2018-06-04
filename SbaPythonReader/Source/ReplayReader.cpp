#include "ReplayReader.h"
#include "Python.h"
#include <QFile>
#include <QTextStream>

ReplayReader::ReplayReader(QString sc2ProtocolPath) {
	_sc2ProtocolPath = sc2ProtocolPath;
	Py_Initialize();
}

ReplayReader::~ReplayReader() {
	Py_Finalize();
}

int ReplayReader::Read(int argCount, char** args) {
	PySys_SetArgv(argCount, args);

	QFile f(_sc2ProtocolPath + "/s2_cli.py");
	if (!f.open(QFile::ReadOnly | QFile::Text)) 
		return static_cast<int>(CouldNotOpenFile);
	QTextStream in(&f);
	QString fileContents = in.readAll();

	// Add the sc2protocol directory to the python path as well
	fileContents.prepend(QString(
		"import sys\n"
		"sys.path.insert(0, '") + _sc2ProtocolPath + QString("')\n"));

	std::string stdContents = fileContents.toStdString();

	// Run the script
	int result = PyRun_SimpleString(stdContents.c_str());

	if (PyErr_Occurred()) {
		PyErr_Print();
		return static_cast<int>(ScriptError);
	}
	
	return result;
}
