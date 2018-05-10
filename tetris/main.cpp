
//main.cpp
#include <QObject>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "controller.h"
#include "mainwindow.h"
#include "teris.h"
#include "map.h"
using namespace Teris;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Player::MainWindow m;
    QGraphicsView v(&m);
    v.show();
    Controller controller;
    return a.exec();
}
