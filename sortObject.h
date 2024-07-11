#ifndef SORTOBJECT_H
#define SORTOBJECT_H
#pragma once

#include<QObject>
#include<QPainter>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QPropertyAnimation>
#include<QGraphicsRectItem>

class rectItem:public QGraphicsRectItem{
public:
    //对构造函数进行改造.现在x,y指的是矩形左下角的坐标而不是原函数规定的右上角
    rectItem(qreal x,qreal y,qreal width,qreal height)
        :QGraphicsRectItem(x,y+height,width,height){}

    void animate(qreal endx,qreal endy,int duration);
};

//抽象化的排序展示类,为提供统一接口而存在
class sortObject :public QObject
{
    Q_OBJECT
public:
    explicit sortObject(QObject *parent = nullptr);

    //开始排序函数
    virtual void sort(int count,int speed)=0;
    virtual void stop()=0;

private:

};


#endif // SORTOBJECT_H


