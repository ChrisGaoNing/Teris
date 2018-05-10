#ifndef Teris_H
#define Teris_H

#include <QObject>
#include <QGraphicsItemGroup>
#include <QList>
#include <QGraphicsColorizeEffect>
#include <QTransform>
#include <QPair>

#include "constants.h"
namespace Teris
{
class Controller;
class Block;
class GameMap;
class Teris :public QObject,public QGraphicsItemGroup
{
    Q_OBJECT
public:

    typedef enum
    {
        NEXT,
        FALL,
        LEFT,
        RIGHT,
        DOWN,
        STOP,
        TURN
    } Action;
    typedef enum
    {
        I,
        L,
        RL,
        Z,
        RZ,
        T,
        O,
    }TerisType;
    typedef int angle;

    Teris(qreal x,qreal y,int speed,GameMap* map,QObject* parent = 0);
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void reset(int type);
    void setType(TerisType type);
    void setAction(Action action);
    Action getAction()const;
    void create();
    void resetPos();
    ~Teris();
signals:
    void gameOver();
protected:
    void move();
    void fall();
    void advance(int phase);
    QPair<qreal,qreal> sendBlockToMap();
    bool isColliding();
private:

    bool _over;
    TerisType _type;
    QList<Block*> _block;
    QPointF _startPos;
    angle _currentAngle;
    int _speed;
    int _counter;
    Action _action;
    QGraphicsColorizeEffect* _colorEffect;
    GameMap* _map;
    int _nextType;
};
}
#endif // Teris_H
