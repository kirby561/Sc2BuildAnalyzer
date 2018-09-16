#include "startscreen.h"
#include "ui_startscreen.h"
#include "ReplayParser.h"
#include "Build.h"
#include "Resources.h"
#include "BuildComparator.h"

StartScreen::StartScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);

    QPixmap bkgnd(Resources::GetPath("Images/logo.jpg"));
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
	ReplayParseResult result = parser.Parse(Resources::GetPath("Replays/Test1.SC2Replay"));
	if (result.Succeeded()) {
		std::pair<Build, Build> builds = Build::FromReplay(result.GetReplay());

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

		delete result.GetReplay();
	} else {
		Log::Error("Failed to load the replay.  Reason: " + result.GetErrorDetails().toStdString());
	}

	// Load 2 replays, compare the first 151 seconds and print the result (should be 0 since the builds are the same up to that point).
	ReplayParseResult result = parser.Parse(Resources::GetPath("Replays/TvZ211Test1.SC2Replay"));
	ReplayParseResult result2 = parser.Parse(Resources::GetPath("Replays/TvZ211Test2.SC2Replay"));

	if (result.Succeeded() && result2.Succeeded()) {
		BuildComparator comparer;
		BuildComparisonParams params;
		params.CompareTimeS = 151;
		comparer.SetBuildComparisonParams(params);

		Build build1 = Build::FromReplay(result.GetReplay()).first;
		Build build2 = Build::FromReplay(result2.GetReplay()).second;
		BuildComparison comparison = comparer.Compare(build1, build2);
		Log::Message(QString("Compare result: %1").arg(comparison.Result).toStdString());

		delete result.GetReplay();
		delete result2.GetReplay();
	} else {
		Log::Error(QString("Failed to load one of the replays. result = %1, result2 = %2").arg(result.GetErrorDetails()).arg(result2.GetErrorDetails()).toStdString());
	}
}

void StartScreen::on_pushButton_2_clicked()
{
	this->close();	
}

StartScreen::~StartScreen()
{
    delete ui;
}
