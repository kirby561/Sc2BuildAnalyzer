#include "ReplayReader.h"
#include <QCoreApplication>
#include <iostream>

int main(int argc, char** argv) {
	QCoreApplication app(argc, argv);
	QString s2ProtocolPath = QCoreApplication::applicationDirPath() + "/s2protocol";
	ReplayReader reader(s2ProtocolPath);
	return reader.Read(argc, argv);
}
