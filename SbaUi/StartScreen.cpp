#include "startscreen.h"
#include "ui_startscreen.h"
#include "ReplayParser.h"
#include "Build.h"
#include "Resources.h"

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

    ReplayParser parser;
	ReplayParseResult result = parser.Parse(Resources::GetPath("Replays/TestReplay1.SC2Replay"));

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
}

void StartScreen::on_pushButton_2_clicked()
{
	this->close();	
}

StartScreen::~StartScreen()
{
    delete ui;
}
