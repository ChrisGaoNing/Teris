
//map.cpp
#include <QPainter>
#include <QBrush>
#include <QPixmap>
#include <QDebug>
#include <QGraphicsItemGroup>
#include <QGraphicsOpacityEffect>
#include <QPixmap>

#include "map.h"
#include "teris.h"
namespace Teris
{
GameMap::GameMap():
    QGraphicsScene(),
    _nextTeris(new Teris(mapWidth,-0.2*mapLength,0,this)),
    _scoreText(new QGraphicsTextItem()),
    _score(0)
{
    _nextTeris->setAction(Teris::NEXT);
    updateScore(0);
    _scoreText->setPos(0.6*mapWidth,0.2*mapLength);
    QFont scoreTextFont;
    scoreTextFont.setPixelSize(20);
    _scoreText->setFont(scoreTextFont);
    _scoreText->setDefaultTextColor(Qt::white);
    setSceneRect(-mapWidth,-mapLength,5*mapWidth,3*mapWidth);
    addItem(_nextTeris);
    addItem(_scoreText);
    init();

}
void GameMap::init()
{
    QPen linePen(Qt::white,1,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin);
    for(int i = 0;i<4;i++)
    {
        _boundary.push_back(new QGraphicsLineItem());
        _boundary.back()->setPen(linePen);
        addItem(_boundary.back());
    }
    _boundary.at(0)->setLine(-0.5*mapWidth-1,-0.5*mapLength-1,0.5*mapWidth+1,-0.5*mapLength-1);
    _boundary.at(1)->setLine(-0.5*mapWidth-1,0.5*mapLength+1,0.5*mapWidth+1,0.5*mapLength+1);
    _boundary.at(2)->setLine(-0.5*mapWidth-1,-0.5*mapLength-1,-0.5*mapWidth-1,0.5*mapLength+1);
    _boundary.at(3)->setLine(0.5*mapWidth+1,-0.5*mapLength-1,0.5*mapWidth+1,0.5*mapLength-1);
    setBackgroundBrush(Qt::black);
}
void GameMap::clearBlock(QList<QGraphicsItem *> block)
{
    QRect rect(-0.5*mapWidth,-0.5*mapLength,mapWidth,block.at(0)->y()-blockWidth+0.5*mapLength);
    foreach(QGraphicsItem* one,block)
    {
        removeItem(one);
        delete one;
    }
    QList<QGraphicsItem*> itemsDown = items(rect);
    foreach(QGraphicsItem* item,itemsDown)
    {
        item->moveBy(0,blockWidth);
    }
}

void GameMap::deleteLine(QPair<qreal, qreal> minMax)
{
    int score = 0;
    for(minMax.first;minMax.first < minMax.second + 1; minMax.first += blockWidth)
    {
        QRectF rect(-0.5*mapWidth,minMax.first-0.5*blockWidth,mapWidth,blockWidth);
        QList<QGraphicsItem*> oneLineBlock = items(rect);
        if(oneLineBlock.size() == (mapWidth/blockWidth)-1)
        {
            clearBlock(oneLineBlock);
            score++;
        }
    }
    updateScore(score);
}
void GameMap::removeAll()
{
    QRectF map(-0.5*mapWidth,-0.5*mapLength,mapWidth,mapLength);
    QList<QGraphicsItem*> allBlocks = items(map);
    foreach(QGraphicsItem* one,allBlocks)
    {
        removeItem(one);
        delete one;
    }
    _scoreText->setPlainText(QString("0"));
}
void GameMap::createNextTeris(int type)
{
    Teris::TerisType nextType;
    switch(type)
    {
    case 0:
        nextType = Teris::I;
        break;
    case 1:
        nextType = Teris::L;
        break;
    case 2:
        nextType = Teris::RL;
        break;
    case 3:
        nextType = Teris::Z;
        break;
    case 4:
        nextType = Teris::RZ;
        break;
    case 5:
        nextType = Teris::T;
        break;
    case 6:
        nextType = Teris::O;
        break;
    default:
        break;
    }
    _nextTeris->setType(nextType);
    _nextTeris->create();
}
void GameMap::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->save();
    QPixmap px(":images/background");
    if(!px.isNull())
    {
        painter->drawPixmap(-mapWidth,-mapLength,5*mapWidth,3*mapWidth,px);
    }
    else
    {
        qDebug() <<"can't find picture";
    }
    painter->restore();
}
void GameMap::updateScore(int value)
{
    _score += value;
    QString score = QString("Your score is :%1").arg(_score);
    _scoreText->setPlainText(score);
}
}
