#ifndef SORTOBJECT_H
#define SORTOBJECT_H

#include "basecanva.h"

//排序算法抽象基类.
class SortObject : public QObject
{
    Q_OBJECT
public:
    explicit SortObject(int type,BaseCanva* canva,QObject *parent = nullptr)
        : QObject{parent}
        , type(type)
        , canva(canva)
    {
        connect(this,&SortObject::swapSignal,canva,&BaseCanva::animatedSwap);
        connect(this,&SortObject::cmpSignal,canva,&BaseCanva::animatedCmp);
    }

    //排序算法函数.这一函数应该放有排序算法的核心逻辑.
    //其中的每次进行比较和交换的时候,都请使用emit发送一次对应的信号实现对BaseCanva类中对应绘图功能的调用.
    //各位在编写时不需要考虑线程问题.上级的SortDisplay窗口会将该函数分配到一个单独的线程.
    virtual void sort(int count,int interval) = 0;

public slots:
    //暂停函数,由GUI线程发出信号激活.
    void pause(){
        singleStepMode = true;
    }

signals:
    void swapSignal();
    void cmpSignal(int i,int j);

private:
    //请通过该指针,使用at()函数访问样本数据.
    std::vector<int>* sample;

    int type = -1;

    //指示排序状态.如果该值为true,则表明展示当前处于单步执行状态,等待用户按下"下一步"或"开始排序"
    //如果为false,则表明当前处于连续执行状态.等待用户按下"暂停排序"或排序完成信号.
    bool singleStepMode = false;
    BaseCanva* canva;
};

#endif // SORTOBJECT_H
