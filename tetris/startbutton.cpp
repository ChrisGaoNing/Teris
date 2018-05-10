
//startbutton.cpp
#include <QPainter>

#include "startbutton.h"
#include "controller.h"
#include "constants.h"
namespace Teris
{
StartButton::StartButton(qreal width, qreal height, qreal x, qreal y, Controller *controller):
    MainSceneButton(QString("Start"),width,height,x,y,controller)
{

}
QRectF StartButton::boundingRect()const
{
    QRectF rect(-0.5*_width,-0.5*_height,_width,_height);
    return rect;
}
void StartButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}
void StartButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    _controller->startGame();
}
}
