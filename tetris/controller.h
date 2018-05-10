#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsView>
namespace Teris
{
class Teris;
class GameMap;
class MainScene;
class Controller:public QObject
{
    Q_OBJECT
public:
    Controller(QObject* parent = 0);
    virtual ~Controller();
    bool eventFilter(QObject *watched, QEvent *event);
    QTimer* _timer;
public slots:
    void gameOver();
    virtual void startGame();
    void pause();
    void resume();
private:
    MainScene* _mainScene;
    GameMap* _map;
    Teris* _teris;
    QGraphicsView* _view;

};
}
#endif // CONTROLLER_H
