#ifndef BASECANVA_H
#define BASECANVA_H

#include <QObject>
#include <QWidget>
#include "sortobject.h"

class RectItem:public QGraphicsRectItem{

public:
    //对构造函数进行改造.现在x,y指的是矩形左下角的坐标而不是原函数规定的右上角
    RectItem(qreal x,qreal y,qreal width,qreal height)
        :QGraphicsRectItem(x,y+height,width,height)
        ,xpos(x)
        ,ypos(y){}

    //注意:此处两个坐标均为左下角的坐标
    qreal xpos,ypos;
};


////////////
/// \brief The Animate class
/// 为多线程执行动画准备的一个形式上的类
class Animate:public QObject{
    Q_OBJECT

public slots:
    void execute();
signals:
    void finished();
public:
    Animate(RectItem* rectItem,qreal endx,qreal endy,int duration):rectItem(rectItem)
        ,endx(endx)
        ,endy(endy)
        ,duration(duration)
    {}

private:
    RectItem* rectItem;
    qreal endx,endy;
    int duration;
    QPropertyAnimation animation;
};


////////////
/// \brief The BaseCanva class
/// 画布控件类
class BaseCanva : public QWidget
{
    Q_OBJECT
public:
    explicit BaseCanva(QWidget *parent = nullptr);

    void sort(int cnt,int interval);
    void pause();
    void setSortParameter(SortObject* in,std::vector<int>* sampleIn);

    static void animatedSwap(RectItem* start,RectItem* destination,int duration);

signals:
    void statusChanged(bool running);

public:
    SortObject *sortObj=nullptr;
    std::vector<int>* sample;
    std::vector<RectItem*> allRect;
};

#endif // BASECANVA_H
