#include "basecanva.h"
#include <QDebug>

BaseCanva::BaseCanva(QWidget *parent)
    : QGraphicsView{parent}
{
    setAttribute(Qt::WA_StyledBackground,true);
    scene = new QGraphicsScene(this);
    this->setScene(scene);
    scene->setSceneRect(this->rect());
    this->show();
}

//绘制最初状态下的样本
void BaseCanva::initializeRect()
{
    //画布大小参数
    const int width=this->width();
    const int height=this->height();

    //样本状态参数
    cap = sample->size();
    maxVal = *std::max_element(sample->begin(),sample->end());
    minVal = *std::min_element(sample->begin(),sample->end());
    maxDifference = maxVal-minVal;

    //以下是计算获得的每个长方体的大小参数
    const int averageWidth=width/cap;
    const int heightWeight=(height-topSpace)/maxDifference;

    for(int i=0;i<sample->size();i++){
        int tempHeight=heightWeight*sample->at(i);
        // 这里的 (0, 0) 是相对于矩形项自身坐标系的位置
        RectItem* temp = new RectItem(0, 0, averageWidth, tempHeight);
        temp->setBrush(Qt::white);

        // 这里的 setPos 设置的是矩形在场景中的位置
        temp->setPos(leftSpace + averageWidth * i, height - bottomSpace - tempHeight);
        allRect.push_back(temp);
        scene->addItem(temp);
    }

    return;
}


//矩形尺寸更新函数
void BaseCanva::repaintRect()
{
    //画布大小参数
    const int width=this->width();
    const int height=this->height();

    //以下是计算获得的每个长方体的大小参数
    const int averageWidth=width/cap;
    const int heightWeight=(height-topSpace)/maxDifference;

    for(int i=0;i<cap;i++){
        int tempHeight=heightWeight*sample->at(i);

        // 这里的 setPos 设置的是矩形在场景中的位置
        allRect[i]->setRect(0, 0, averageWidth, tempHeight);
        allRect[i]->setPos(leftSpace + averageWidth * i, height - bottomSpace - tempHeight);
    }

    return;
}


//画布接收数据函数
void BaseCanva::setSortParameter(SortObject *in,std::vector<int>* sampleIn)
{
    sortObj=in;
    sample=sampleIn;
    return;
}


//交换函数,会自动进行颜色标记
void BaseCanva::animatedSwap(int i,int j)
{
    int duration = interval;
    swapping1 = i;
    swapping2 = j;
    RectItem *start = allRect[i];
    RectItem *destination = allRect[j];
    start->setBrush(Qt::red);
    destination->setBrush(Qt::red);

    QPointF pos1 = start->pos();
    QPointF pos2 = destination->pos();

    QPropertyAnimation *anime1=new QPropertyAnimation(start,"pos");
    anime1->setDuration(duration);
    anime1->setStartValue(pos1);
    anime1->setEndValue(QPointF(pos2.x(),pos1.y()));
    anime1->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation *anime2=new QPropertyAnimation(destination,"pos");
    anime2->setDuration(duration);
    anime2->setStartValue(pos2);
    anime2->setEndValue(QPointF(pos1.x(),pos2.y()));
    anime2->start(QAbstractAnimation::DeleteWhenStopped);

    anime1->start();
    anime2->start();
    connect(anime2,&QPropertyAnimation::finished,this,&BaseCanva::cancelSwapMark);

    return;
}


//比较函数,效果上相当于返回sample[i]<sample[j].在编写排序算法时,进行样本间比较请使用该函数.
bool BaseCanva::lessCmp(int i, int j)
{
    allRect[i]->setBrush(QColor(0x33ccff));
    allRect[j]->setBrush(QColor(0x33ccff));
    QTimer* temp = new QTimer(this);
    temp->isSingleShot();
    connect(temp,&QTimer::timeout,this,[=](){
        allRect[i]->setBrush(Qt::white);
        allRect[j]->setBrush(Qt::white);
        temp->deleteLater();
    });
    temp->start(interval);
    return sample->at(i)<sample->at(j);
}


//取消标记函数.会自动调用,不要手动调用.
void BaseCanva::cancelSwapMark()
{
    allRect[swapping1]->setBrush(Qt::white);
    allRect[swapping2]->setBrush(Qt::white);
    swapping1 = swapping2 = 0;
    return;
}


//全局窗口中画布的自适应更新大小函数
void BaseCanva::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    scene->setSceneRect(this->rect());
    if(cap)
        repaintRect();
    return;
}

