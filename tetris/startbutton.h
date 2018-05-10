#ifndef STARTBUTTON_H
#define STARTBUTTON_H
#include <QLinearGradient>

#include "mainscenebutton.h"

namespace Teris
{
class StartButton:public MainSceneButton
{
public:
   StartButton(qreal width, qreal height, qreal x, qreal y, Controller* controller);
   QRectF boundingRect() const;
   void mousePressEvent(QGraphicsSceneMouseEvent* event);
   void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
};
}
#endif // STARTBUTTON_H
