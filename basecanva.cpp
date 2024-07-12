#include "basecanva.h"

BaseCanva::BaseCanva(QWidget *parent)
    : QGraphicsView{parent}
{
    setAttribute(Qt::WA_StyledBackground,true);
    scene = new QGraphicsScene(this);
    this->setScene(scene);

    this->show();
}

//绘制最初状态下的样本
void BaseCanva::initializeRect()
{
    //画布大小参数
    const int width=this->width();
    const int height=this->height();
    //样本状态参数
    const int cap=sample->size();
    const int maxVal=*std::max_element(sample->begin(),sample->end());
    const int minVal=*std::min_element(sample->begin(),sample->end());
    //显示边框预留空位宽度
    const int leftSpace =0;
    const int rightSpace=0;
    const int topSpace=0;
    const int bottomSpace=0;

    //以下是计算获得的每个长方体的大小参数
    const int maxDifference=maxVal-minVal;
    const int averageWidth=width/cap;
    const int heightWeight=(height-topSpace)/maxDifference;

    for(int i=0;i<sample->size();i++){
        int tempHeight=heightWeight*sample->at(i);
        RectItem* temp = new RectItem(leftSpace+averageWidth*i,height-bottomSpace-tempHeight,averageWidth,tempHeight);
        temp->setBrush(Qt::white);
        allRect.push_back(temp);
        scene->addItem(temp);
    }
    scene->setSceneRect(this->rect());
    return;
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
    Animate* anime1 = new Animate(start,destination->x(),destination->y(),duration);
    Animate* anime2 = new Animate(destination,start->x(),start->y(),duration);
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
    QPropertyAnimation *animation=new QPropertyAnimation(rectItem,"pos");
    animation->setDuration(duration);
    animation->setStartValue(rectItem->pos());
    animation->setEndValue(QPointF(endx,endy));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    emit finished();
    return;
}
