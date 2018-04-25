
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
    Controller controller;
    return a.exec();
}
