#include "startscreen.h"
#include "ui_startscreen.h"
#include "ReplayParser.h"

StartScreen::StartScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);

	ReplayParser parser;
	parser.Parse("C:/Users/Alex/Documents/StarCraft II/Accounts/50202609/1-S2-1-1986271/Replays/Multiplayer/Ascension to Aiur LE.SC2Replay");
}

StartScreen::~StartScreen()
{
    delete ui;
}
