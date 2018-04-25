
//mainwindow.cpp

#include <QPainter>
#include <QLinearGradient>

#include "mainwindow.h"
namespace Player
{
MainWindow::MainWindow():
    _linear(new QLinearGradient(sceneRect().topLeft(),sceneRect().bottomRight())),
    _brush(new QBrush(*_linear))
{
    setSceneRect(0,0,500,300);
    _linear->setColorAt(0,QColor(170,170,255));
    _linear->setColorAt(0.3,QColor(188,189,255));
    _linear->setColorAt(0.5,QColor(255,255,255));
    _linear->setColorAt(0.7,QColor(188,189,255));
    _linear->setColorAt(1,QColor(170,170,255));
}

void MainWindow::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->save();
    painter->setBrush(*_brush);
    painter->drawRect(sceneRect());
    painter->restore();
}
}
