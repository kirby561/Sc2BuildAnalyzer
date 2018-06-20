#include "startscreen.h"
#include "ui_startscreen.h"
#include "ReplayParser.h"
#include "Build.h"

StartScreen::StartScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);

    QPixmap bkgnd(".\\Debug\\Resources\\Image\\logo.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::AspectRatioMode::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

	Sc2Unit::InitUnitTable();
    ReplayParser parser;
    //ReplayParseResult result = parser.Parse("C:/Users/Alex/Documents/StarCraft II/Accounts/50202609/1-S2-1-1986271/Replays/Multiplayer/Ascension to Aiur LE.SC2Replay");
	//"C:\Users\Alex\Documents\StarCraft II\Accounts\50202609\1-S2-1-1986271\Replays\Multiplayer\Catalyst LE (37).SC2Replay"
	ReplayParseResult result = parser.Parse("C:/Users/Alex/Documents/StarCraft II/Accounts/50202609/1-S2-1-1986271/Replays/Multiplayer/Catalyst LE (37).SC2Replay");

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
