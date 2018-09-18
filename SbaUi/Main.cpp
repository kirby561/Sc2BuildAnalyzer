#include "StartScreen.h"
#include <QApplication>
#include "Resources.h"
#include "ReplayData/Sc2Unit.h"
#include "WindowManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	// Init resources and static tables
	Resources::Init(QCoreApplication::applicationDirPath() + "/Resources/");
	Sc2Unit::InitUnitTable();

	WindowManager manager;
	manager.Start();

    return a.exec();
}
