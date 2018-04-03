说明：
框架啊：

把一个项目分解成几个块

1.界面是怎么做出来的？ 

2.要有一个形状的类

3.封装继承和多态化；

4.移动的话，需要一个类去管理









分析：

类：

          棋盘：

.cell[][]

+Get cells

+Set cells





父：形状

+color 

+cell[4]

+rotate

方格

+color

+location

+position

游戏引擎

+move

+moveleft

+moveright

+movedown

+generatesharp

+putonboard

主窗口：画图的实现，时间的触发；

+key release

+key press

+paint



要把项目的可扩展性弄好，这样后期

很容易就加上去；



消除：把整个棋盘往下移动一格；
