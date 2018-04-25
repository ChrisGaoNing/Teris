#ifndef MAINSCENEBUTTON_H
#define MAINSCENEBUTTON_H

#include <QGraphicsItem>
#include <QGraphicsOpacityEffect>
#include <QGraphicsDropShadowEffect>

namespace Teris
{
class Controller;
class MainSceneButton:public QGraphicsItem
{
public:
    MainSceneButton(QString caption,qreal width,qreal height,qreal x,qreal y,Controller* controller);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual QRectF boundingRect()const = 0;
    QString getCaption()const;
    void setCaption(QString caption);
    ~MainSceneButton();
protected:
    qreal _width;
    qreal _height;
    QString _caption;
    QGraphicsDropShadowEffect* _shadow;
    Controller* _controller;
    QFont _font;
    QPainterPath _path;
};
}
#endif // MAINSCENEBUTTON_H
