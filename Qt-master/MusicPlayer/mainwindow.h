#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>

namespace Player
{
class MainWindow:public QGraphicsScene
{
public:
    MainWindow();
    void drawBackground(QPainter* painter,const QRectF& rect);
private:
    QLinearGradient* _linear;
    QBrush* _brush;
};
}
#endif // MAINWINDOW_H
