#include "ProjectWindow.h"
#include "Resources.h"
#include "ui_projectwindow.h"
#include <QGraphicsPixmapItem>

ProjectWindow::ProjectWindow(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::ProjectWindow) {
    ui->setupUi(this);

    QImage image(Resources::GetPath("Images/Units/Armory.png"));

    QGraphicsPixmapItem* item = new QGraphicsPixmapItem( QPixmap::fromImage( image ) );
    QGraphicsScene* scene = new QGraphicsScene;
    ui->_graphicsView->setScene( scene );

    scene->addItem( item );
    SetCenter(item, 0, 0);
    item->setScale(1.0f);
    item->setTransformationMode(Qt::SmoothTransformation);

    ui->_graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->_graphicsView->setSceneRect(-1000, -1000, 2000, 2000);
    ui->_graphicsView->show();
}

ProjectWindow::~ProjectWindow() {
    delete ui;
}

void ProjectWindow::SetCenter(QGraphicsItem* item, float x, float y) {
    QRectF boundingRect = item->boundingRect();
    float width = boundingRect.width();
    float height = boundingRect.height();
    item->setPos(x - width / 2.0f, y - height / 2.0f);
}
