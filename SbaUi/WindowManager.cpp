#include "WindowManager.h"

void WindowManager::Start() {
	_activeWindow = new StartScreen(this);
	_activeWindow->show();
}

void WindowManager::SwitchWindows(QWidget* newWindow) {
	QWidget* current = _activeWindow;
	_activeWindow = newWindow;
	newWindow->show();
	current->hide();
	delete current;
}
