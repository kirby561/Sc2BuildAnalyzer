#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QMainWindow>

namespace Ui {
class StartScreen;
}

class WindowManager;

class StartScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartScreen(WindowManager* manager, QWidget *parent = 0);
    virtual ~StartScreen();

private slots:
	void OnNewProjectButtonClicked();
    void OnExitButtonClicked();

private:
    Ui::StartScreen* _ui;
	WindowManager* _windowManager;

	void ConnectSlots();

};

#endif // STARTSCREEN_H
