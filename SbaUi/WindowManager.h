#pragma once

#include <QWidget>
#include "StartScreen.h"

/**
 * This class manages the currently displayed window and transitioning
 *    between them.  The WindowManager also owns the memory for each 
 *    window.
 **/
class WindowManager {
public:
	WindowManager() {}

	void Start();
	void SwitchWindows(QWidget* newWindow);

private:
	QWidget* _activeWindow = nullptr;
};
