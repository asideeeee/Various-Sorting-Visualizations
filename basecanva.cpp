#include "basecanva.h"

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
    maxDifference = maxVal-minVal+1;

    //以下是计算获得的每个长方体的大小参数
    const double averageWidth=width/(double)cap;
    const double heightWeight=(height-topSpace)/(double)maxDifference;

    for(int i=0;i<sample->size();i++){
        double tempHeight=heightWeight*sample->at(i);
        // 这里的 (0, 0) 是相对于矩形项自身坐标系的位置
        RectItem* temp = new RectItem(0, 0, averageWidth, tempHeight);
        temp->setBrush(Qt::white);

        // 这里的 setPos 设置的是矩形在场景中的位置
        allRect.push_back(temp);
        scene->addItem(temp);
        temp->setPos(leftSpace + averageWidth * i, height - bottomSpace - tempHeight);
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
    const double averageWidth=width/(double)cap;
    const double heightWeight=(height-topSpace)/(double)maxDifference;

    for(int i=0;i<cap;i++){
        double tempHeight=heightWeight*sample->at(i);

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
void BaseCanva::animatedCmp(int i, int j)
{
    allRect[lastI]->setBrush(Qt::white);
    allRect[lastJ]->setBrush(Qt::white);
    lastI=i;
    lastJ=j;
    allRect[i]->setBrush(QColor(0x33ccff));
    allRect[j]->setBrush(QColor(0x33ccff));
    return;
}


//在排序完成后请调用该函数,将已经排序完成的样本标成绿色.
void BaseCanva::completeMark()
{
    SortCompleteThread* temp = new SortCompleteThread(cap,&allRect);
    connect(temp, &QThread::finished, temp, &QThread::deleteLater);
    connect(temp,&SortCompleteThread::updateRequest,this,[=]{
        viewport()->update();
    });
    temp->start();
    return;
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

////////////////////////
/// SortCompleteThread类
//辅助线程的函数,不要动它
void SortCompleteThread::run()
{
    for(int i=0;i<cap;i++){
        arr->at(i)->setBrush(Qt::green);
        QThread::msleep(1);
        emit updateRequest();
    }
    return;
}


//////////////////////////
/// \brief SortObject类
void SortObject::swap(int &i, int &j)
{
    std::swap(i,j);
    emit swapSignal(i,j);
    pause();
    return;
}

void SortObject::comparing(int i, int j)
{
    emit cmpSignal(i,j);
    pause();
    return;
}

void SortObject::pause()
{

}


SortObject::SortObject(int type,BaseCanva* canva,QObject *parent)
    : QObject{parent}
    , type(type)
    , canva(canva)
{
    connect(this,&SortObject::swapSignal,canva,&BaseCanva::animatedSwap);
    connect(this,&SortObject::cmpSignal,canva,&BaseCanva::animatedCmp);
    sample=canva->sample;
}

void SortObject::setPause()
{
    singleStepMode = true;
    return;
}

void SortObject::startSort()
{
    singleStepMode = false;
    return;
}

void SortObject::nextStep()
{
    nextStepRequest = true;
    return;
}
