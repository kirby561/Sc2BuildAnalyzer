#include "startscreen.h"
#include <QApplication>
#include "Resources.h"
#include "ReplayData/Sc2Unit.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	// Init resources and static tables
	Resources::Init(QCoreApplication::applicationDirPath() + "/Resources/");
	Sc2Unit::InitUnitTable();

    StartScreen w;
    w.show();

    return a.exec();
}
