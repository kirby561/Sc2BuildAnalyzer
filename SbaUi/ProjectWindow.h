#ifndef PROJECTWINDOW_H
#define PROJECTWINDOW_H

#include <QMainWindow>

class QGraphicsItem;

namespace Ui {
class ProjectWindow;
}

class ProjectWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ProjectWindow(QWidget *parent = 0);
    ~ProjectWindow();

private:
    Ui::ProjectWindow *ui;

    void SetCenter(QGraphicsItem* item, float x, float y);
};

#endif
