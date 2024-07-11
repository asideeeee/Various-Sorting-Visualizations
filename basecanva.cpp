#include "basecanva.h"

BaseCanva::BaseCanva(QWidget *parent)
    : QWidget{parent}
{
    setAttribute(Qt::WA_StyledBackground,true);
}

void BaseCanva::setSortParameter(SortObject *in,std::vector<int>* sampleIn)
{
    sortObj=in;
    sample=sampleIn;
}

//交换函数
void BaseCanva::animatedSwap(RectItem *start, RectItem *destination,int duration)
{
    QThread* thread1=new QThread;
    QThread* thread2=new QThread;
    Animate* anime1 = new Animate(start,destination->xpos,destination->ypos,duration);
    Animate* anime2 = new Animate(destination,start->xpos,start->ypos,duration);
    anime1->moveToThread(thread1);
    anime2->moveToThread(thread2);
    QObject::connect(thread1,&QThread::started,anime1,&Animate::execute);
    QObject::connect(thread2,&QThread::started,anime2,&Animate::execute);
    QObject::connect(anime1, &Animate::finished, thread1, &QThread::quit);
    QObject::connect(anime2, &Animate::finished, thread2, &QThread::quit);
    QObject::connect(thread1, &QThread::finished, anime1, &QObject::deleteLater);
    QObject::connect(thread2, &QThread::finished, anime2, &QObject::deleteLater);
    QObject::connect(thread1, &QThread::finished, thread1, &QObject::deleteLater);
    QObject::connect(thread2, &QThread::finished, thread2, &QObject::deleteLater);

    thread1->start();
    thread2->start();

    return;
}

//动画执行函数
void Animate::execute()
{
    emit finished();
}
