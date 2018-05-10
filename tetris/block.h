#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsItem>
#include <QRectF>
#include <QPainterPath>
#include <QColor>
#include <QPointF>
namespace Teris
{

class Block:public QGraphicsItem
{
public:
    Block();
    Block(qreal x,qreal y);
    Block(QPointF pos);
    Block(Block& other);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape()const;
    QRectF boundingRect()const;
};
}
#endif // BLOCK_H
