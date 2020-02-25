#include "startscreen.h"
#include "ui_startscreen.h"
#include "ReplayParser.h"
#include "Build.h"
#include "Resources.h"
#include "BuildComparator.h"
#include "ProjectWindow.h"
#include "WindowManager.h"
#include "Project.h"
#include "ProgressListener.h"
#include <future>

class ReplayAddListener : public ProgressListener {
public:
	ReplayAddListener() {
		_result = _resultPromise.get_future();
	}

	virtual void OnProgressChanged(int progress, int max) {
		Log::Message(QString("Progress: %1, Max: %2").arg(progress).arg(max).toStdString());
	}

	virtual void OnFinished(int result) {
		Log::Message(QString("Finished with result %1").arg(result).toStdString());
		_resultPromise.set_value(result);
	}

	int GetResult() { return _result.get(); }

private:
	std::promise<int> _resultPromise;
	std::future<int> _result;
};

void WriteDataObjectToFile(DataObject* obj, QString fileName) {
	QFile file(fileName);
	file.open(QIODevice::WriteOnly);
	file.write(obj->ToString().toUtf8());
	file.close();
}

StartScreen::StartScreen(WindowManager* manager, QWidget *parent) :
		QMainWindow(parent),
		_windowManager(manager),
		_ui(new Ui::StartScreen) {
    _ui->setupUi(this);
	ConnectSlots();

    QPixmap bkgnd(Resources::GetPath("Images/Logo.jpg"));
    bkgnd = bkgnd.scaled(this->size(), Qt::AspectRatioMode::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);


	///
	/// The following is test code just to play around with replay loading and builds.  It will be deleted
	///    when we have an actual application going but it convenient to keep here for the moment.
	///
    ReplayParser parser;

	// Loads a replay and print both builds to the terminal.
	ReplayParseResult resultTest1 = parser.Parse(Resources::GetPath("Replays/Test1.SC2Replay"));
	if (resultTest1.Succeeded()) {
		std::pair<Build*, Build*> builds = Build::FromReplay(resultTest1.GetReplay());

		WriteDataObjectToFile(resultTest1.GetReplay(), "E:/trash/ReplayTest.json");
		WriteDataObjectToFile(builds.first, "E:/trash/BuildTest1.json");
		WriteDataObjectToFile(builds.second, "E:/trash/BuildTest2.json");

		Log::Message("Player 1s Build:");
		const QList<BuildEntry*>& order = builds.first->GetOrder();
		for (auto entryItr = order.begin(); entryItr != order.end(); entryItr++) {
			BuildEntry* entry = *entryItr;
			Log::Message(QString("\t%1: %2").arg(entry->TimestampSecs).arg(entry->Unit->GetUnitName()).toStdString());
		}

		Log::Message("Player 2s Build:");
		const QList<BuildEntry*>& order2 = builds.second->GetOrder();
		for (auto entryItr = order2.begin(); entryItr != order2.end(); entryItr++) {
			BuildEntry* entry = *entryItr;
			Log::Message(QString("\t%1: %2").arg(entry->TimestampSecs).arg(entry->Unit->GetUnitName()).toStdString());
		}

		delete resultTest1.GetReplay();
	} else {
		Log::Error("Failed to load the replay.  Reason: " + resultTest1.GetErrorDetails().toStdString());
	}

	// Load 2 replays, compare the first 151 seconds and print the result (should be 0 since the builds are the same up to that point).
	ReplayParseResult result = parser.Parse(Resources::GetPath("Replays/TvZ211Test1.SC2Replay"));
	ReplayParseResult result2 = parser.Parse(Resources::GetPath("Replays/TvZ211Test2.SC2Replay"));
	ReplayParseResult result3 = parser.Parse(Resources::GetPath("Replays/TvZ211Test4.SC2Replay"));

	if (result.Succeeded() && result2.Succeeded()) {
		BuildComparator comparer;

		Build* build1 = Build::FromReplay(result.GetReplay()).first;
		Build* build2 = Build::FromReplay(result2.GetReplay()).second;
		Build* build3 = Build::FromReplay(result2.GetReplay()).second;
		BuildComparison comparison = comparer.Compare(build1, build2);
		Log::Message(QString("Compare result: %1").arg(comparison.Result).toStdString());
		
		BuildComparison comparison2 = comparer.Compare(build2, build3);
		Log::Message(QString("Compare result2: %1").arg(comparison2.Result).toStdString());

		delete result.GetReplay();
		delete result2.GetReplay();
		delete result3.GetReplay();
	} else {
		Log::Error(QString("Failed to load one of the replays. result = %1, result2 = %2").arg(result.GetErrorDetails()).arg(result2.GetErrorDetails()).toStdString());
	}

	Project* project = Project::Load("E:/trash/TestProject3/TestProject3.sba");
	//project->Save();

	ReplayAddListener* listener = new ReplayAddListener();
	project->LoadReplays(listener);
	Log::Message(QString("Finished.  Result = %1").arg(listener->GetResult()).toStdString());
	delete listener;

	project->ComputeReplayStats();

	Log::Message("Done");

	//ReplayAddListener* listener = new ReplayAddListener();
	//project->AddReplays("C:/Users/Alex/Documents/StarCraft II/Accounts/50202609/1-S2-1-1986271/Replays/Multiplayer", listener);
	//Log::Message(QString("Result = %1").arg(listener->GetResult()).toStdString());
	//delete listener;	
}

void StartScreen::OnNewProjectButtonClicked() {
	_windowManager->SwitchWindows(new ProjectWindow());
}

void StartScreen::OnExitButtonClicked() {
	this->close();	
}

StartScreen::~StartScreen() {
    delete _ui;
}

void StartScreen::ConnectSlots() {
	connect(_ui->_newProjectButton, SIGNAL(pressed()), this, SLOT(OnNewProjectButtonClicked()));
	connect(_ui->_exitButton, SIGNAL(pressed()), this, SLOT(OnExitButtonClicked()));
}
