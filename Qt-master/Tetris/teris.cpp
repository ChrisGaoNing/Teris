
//Teris_CPP
#include <QPainter>
#include <QTransform>
#include <QDebug>

#include "block.h"
#include "constants.h"
#include "map.h"
#include "teris.h"
#include "time.h"
#include "controller.h"
namespace  Teris
{
Teris::Teris(qreal x, qreal y, int speed, GameMap* map, QObject* parent):
    QObject(parent),
    _over(false),
    _startPos(x,y),
    _currentAngle(0),
    _speed(speed),
    _counter(0),
    _colorEffect(new QGraphicsColorizeEffect()),
    _map(map),
    _action(FALL)
{
    for(int i = 0;i<4;i++)
    {
        Block* block = new Block();
        _block<<block;
        addToGroup(block);
    }
    setPos(x,y);
    this->setGraphicsEffect(_colorEffect);
}
void Teris::create()
{
    switch(_type)
    {
    case L:
        _colorEffect->setColor(QColor(255,0,0));
        _block.at(0)->setPos(-0.5*blockWidth,-1.5*blockWidth);
        _block.at(1)->setPos(-0.5*blockWidth,-0.5*blockWidth);
        _block.at(2)->setPos(-0.5*blockWidth,0.5*blockWidth);
        _block.at(3)->setPos(0.5*blockWidth,0.5*blockWidth);
        break;
    case RL:
         _colorEffect->setColor(QColor(0,255,0));
         _block.at(0)->setPos(0.5*blockWidth,-1.5*blockWidth);
         _block.at(1)->setPos(0.5*blockWidth,-0.5*blockWidth);
         _block.at(2)->setPos(0.5*blockWidth,0.5*blockWidth);
         _block.at(3)->setPos(-0.5*blockWidth,0.5*blockWidth);
        break;
    case I:
        _colorEffect->setColor(QColor(0,0,255));
        _block.at(0)->setPos(-1.5*blockWidth,-0.5*blockWidth);
        _block.at(1)->setPos(-0.5*blockWidth,-0.5*blockWidth);
        _block.at(2)->setPos(0.5*blockWidth,-0.5*blockWidth);
        _block.at(3)->setPos(1.5*blockWidth,-0.5*blockWidth);
        break;
    case T:
        _colorEffect->setColor(QColor(255,85,0));
        _block.at(0)->setPos(-0.5*blockWidth,-0.5*blockWidth);
        _block.at(1)->setPos(-1.5*blockWidth,0.5*blockWidth);
        _block.at(2)->setPos(-0.5*blockWidth,0.5*blockWidth);
        _block.at(3)->setPos(0.5*blockWidth,0.5*blockWidth);
        break;
    case Z:
        _colorEffect->setColor(QColor(255,0,127));
        _block.at(0)->setPos(-1.5*blockWidth,-0.5*blockWidth);
        _block.at(1)->setPos(-0.5*blockWidth,-0.5*blockWidth);
        _block.at(2)->setPos(-0.5*blockWidth,0.5*blockWidth);
        _block.at(3)->setPos(0.5*blockWidth,0.5*blockWidth);
        break;
    case RZ:
        _colorEffect->setColor(QColor(170,85,255));
        _block.at(0)->setPos(1.5*blockWidth,-0.5*blockWidth);
        _block.at(1)->setPos(0.5*blockWidth,-0.5*blockWidth);
        _block.at(2)->setPos(0.5*blockWidth,0.5*blockWidth);
        _block.at(3)->setPos(-0.5*blockWidth,0.5*blockWidth);
        break;
    case O:
        _colorEffect->setColor(QColor(255,255,0));
        _block.at(0)->setPos(-0.5*blockWidth,-0.5*blockWidth);
        _block.at(1)->setPos(-0.5*blockWidth,0.5*blockWidth);
        _block.at(2)->setPos(0.5*blockWidth,-0.5*blockWidth);
        _block.at(3)->setPos(0.5*blockWidth,0.5*blockWidth);
        break;
    default:
        break;
    }
}
QRectF Teris::boundingRect()const
{
    QRectF rect(-2*blockWidth,-2*blockWidth,
                  4*blockWidth,4*blockWidth);
     return rect;
}
void Teris::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
bool Teris::isColliding()
{
    QList<QGraphicsItem*> child = childItems();
    foreach(QGraphicsItem* one,child)
    {
        QList<QGraphicsItem*> colliding = one->collidingItems();
        if(colliding.size() > 0 && !(colliding.size() == 1 && colliding.at(0) == this))
        {
            return true;
        }
    }
    return false;
}

void Teris::fall()
{
    QPointF oldPos= this->pos();
    moveBy(0,blockWidth/2);
    if(isColliding())
    {
        setPos(oldPos);
        _action = STOP;
        return;
    }
}
void Teris::move()
{
    switch(_action)
    {
    case LEFT:
    {
        moveBy(-blockWidth,0);
        if(isColliding())
        {
            moveBy(blockWidth,0);
        }
        break;
    }
    case RIGHT:
    {
        moveBy(blockWidth,0);
        if(isColliding())
        {
            moveBy(-blockWidth,0);
        }
        break;
    }
    case DOWN:
    {
        _counter = _speed;
        break;
    }
    case TURN:
    {
        _currentAngle += 90;
        if(_currentAngle == 360)
        {
            _currentAngle = 0;
        }
        setRotation(_currentAngle);
        if(isColliding())
        {
                _currentAngle -= 90;
                 setRotation(_currentAngle);
        }
        break;
    }
    default:
        break;
    }
}
void Teris::advance(int phase)
{
    if(_action != NEXT && !_over)
    {
        if(!phase)return;
        if(++_counter < _speed)return;
        _counter = 0;
        move();
        fall();
        if(_action != STOP)
        {
             _action = FALL;
        }
        else
        {
            QPair<qreal,qreal> minMax = sendBlockToMap();
            setPos(_startPos);
             _map->deleteLine(minMax);
             reset(_nextType);
        }
    }
}
QPair<qreal, qreal> Teris::sendBlockToMap()
{
    QPair<qreal,qreal> minMax;
    minMax.first = _block.at(0)->scenePos().y();
    minMax.second = _block.at(0)->scenePos().y();
    foreach(Block* block,_block)
    {
        minMax.first = block->scenePos().y()< minMax.first ? block->scenePos().y() : minMax.first;
        minMax.second = block->scenePos().y() > minMax.second ? block->scenePos().y() : minMax.second;
        Block *oldBlock = new Block(block->scenePos());
        _map->addItem(oldBlock);
    }
    return minMax;
}
void Teris::resetPos()
{
    setPos(_startPos);
}

void Teris::reset(int type)
{
    setRotation(0);
    qsrand((unsigned int)time(0));
    _action = FALL;
    _nextType = qrand() % 7;
    switch(type)
    {
    case 0:
        _type = I;
        break;
    case 1:
        _type = L;
        break;
    case 2:
        _type =RL;
        break;
    case 3:
        _type = Z;
        break;
    case 4:
        _type = RZ;
        break;
    case 5:
        _type = T;
        break;
    case 6:
        _type = O;
        break;
    default:
        break;
    }
    create();
     _map->createNextTeris(_nextType);
    if(isColliding())
    {
        _over = true;
        emit gameOver();
    }
}
void Teris::setType(TerisType type)
{
    _type = type;
}
Teris::~Teris()
{
    _block.clear();
    delete _colorEffect;
}
void Teris::setAction(Action action)
{
    _action = action;
}
Teris::Action Teris::getAction()const
{
    return _action;
}
}

