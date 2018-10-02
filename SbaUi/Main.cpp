#include "StartScreen.h"
#include <QApplication>
#include "Resources.h"
#include "ReplayData/Sc2Unit.h"
#include "WindowManager.h"
#include "UtilityTester.h"

int main(int argc, char *argv[]) {
	int result = 0;

	// Quick test implementation to have somewhere to call them
	//    This can be replaced with a more permanent test solution
	if (argc == 2 && QString(argv[1]) == "Test") {
		UtilityTester tester;

		Log::Message("Running tests...");
		if (tester.RunTests()) {
			Log::Message("All tests passed.");
		} else {
			QString log = tester.GetLog();
			Log::Error("One or more tests failed.  Log: ");
			Log::Message(log.toStdString());
			result = -1;
		}
	} else {
		QApplication a(argc, argv);

		// Init resources and static tables
		Resources::Init(QCoreApplication::applicationDirPath() + "/Resources/");
		Sc2Unit::InitUnitTable();

		WindowManager manager;
		manager.Start();

		result = a.exec();
	}

	return result;
}
