#include "startscreen.h"
#include "ui_startscreen.h"
#include "ReplayParser.h"

StartScreen::StartScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);

	ReplayParser parser("C:/Users/Alex/Documents/Code/Sc2BuildAnalyzer/SbaCore/Dependencies/s2protocol/s2_cli.py");
	parser.Parse("Yo");
}

StartScreen::~StartScreen()
{
    delete ui;
}
