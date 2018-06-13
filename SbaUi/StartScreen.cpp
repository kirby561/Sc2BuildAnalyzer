#include "startscreen.h"
#include "ui_startscreen.h"
#include "ReplayParser.h"

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

    ReplayParser parser;
    ReplayParseResult result = parser.Parse("C:/Users/Alex/Documents/StarCraft II/Accounts/50202609/1-S2-1-1986271/Replays/Multiplayer/Ascension to Aiur LE.SC2Replay");
}

void StartScreen::on_pushButton_2_clicked()
{
	this->close();	
}

StartScreen::~StartScreen()
{
    delete ui;
}
