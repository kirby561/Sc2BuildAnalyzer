#include "startscreen.h"
#include "ui_startscreen.h"
#include "ReplayParser.h"

StartScreen::StartScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);

	ReplayParser parser;
	parser.Parse("Yo");
}

StartScreen::~StartScreen()
{
    delete ui;
}
