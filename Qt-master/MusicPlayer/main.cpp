
#include <QApplication>
#include <QGraphicsView>
#include "mainwindow.h"

using namespace Player;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow m;
    QGraphicsView v(&m);
    v.show();
    return a.exec();
}
