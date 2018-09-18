#include "startscreen.h"
#include "ui_startscreen.h"
#include "ReplayParser.h"
#include "Build.h"
#include "Resources.h"
#include "BuildComparator.h"
#include "ProjectWindow.h"
#include "WindowManager.h"

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
		std::pair<Build, Build> builds = Build::FromReplay(resultTest1.GetReplay());

		Log::Message("Player 1s Build:");
		const QList<BuildEntry>& order = builds.first.GetOrder();
		for (auto entryItr = order.begin(); entryItr != order.end(); entryItr++) {
			Log::Message(QString("\t%1: %2").arg(entryItr->TimestampSecs).arg(entryItr->Unit.GetUnitName()).toStdString());
		}

		Log::Message("Player 2s Build:");
		const QList<BuildEntry>& order2 = builds.second.GetOrder();
		for (auto entryItr = order2.begin(); entryItr != order2.end(); entryItr++) {
			Log::Message(QString("\t%1: %2").arg(entryItr->TimestampSecs).arg(entryItr->Unit.GetUnitName()).toStdString());
		}

		delete resultTest1.GetReplay();
	} else {
		Log::Error("Failed to load the replay.  Reason: " + resultTest1.GetErrorDetails().toStdString());
	}

	// Load 2 replays, compare the first 151 seconds and print the result (should be 0 since the builds are the same up to that point).
	ReplayParseResult result = parser.Parse(Resources::GetPath("Replays/TvZ211Test1.SC2Replay"));
	ReplayParseResult result2 = parser.Parse(Resources::GetPath("Replays/TvZ211Test2.SC2Replay"));
	ReplayParseResult result3 = parser.Parse(Resources::GetPath("Replays/TvZ211Test3.SC2Replay"));

	if (result.Succeeded() && result2.Succeeded()) {
		BuildComparator comparer;

		Build build1 = Build::FromReplay(result.GetReplay()).first;
		Build build2 = Build::FromReplay(result2.GetReplay()).second;
		Build build3 = Build::FromReplay(result2.GetReplay()).second;
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
