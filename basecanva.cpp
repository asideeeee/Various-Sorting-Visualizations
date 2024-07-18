#include "basecanva.h"

BaseCanva::BaseCanva(QWidget *parent)
    : QGraphicsView{parent}
{
    setAttribute(Qt::WA_StyledBackground,true);
    scene = new QGraphicsScene(this);
    this->setScene(scene);
    scene->setSceneRect(this->rect());
    this->setBackgroundBrush(Qt::darkGray);
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


//交换函数,会自动进行颜色标记
void BaseCanva::animatedSwap(int i,int j)
{
    allRect[lastI]->setBrush(Qt::white);
    allRect[lastJ]->setBrush(Qt::white);
    int duration = interval;
    swapping1 = i;
    swapping2 = j;
    if(!withdrawing){
        //如果不是在撤回,记录已执行操作
        withdrawSortObj->executedIsSwap.push_back(true);
        withdrawSortObj->executedInfo.push_back(std::make_pair(i,j));
    }
    RectItem *start = allRect[i];
    RectItem *destination = allRect[j];
    start->setBrush(Qt::red);
    destination->setBrush(Qt::red);

    QPointF pos1 = start->pos();
    QPointF pos2 = destination->pos();

    //动画1
    QPropertyAnimation *anime1=new QPropertyAnimation(start,"pos");
    anime1->setDuration(duration);
    anime1->setStartValue(pos1);
    anime1->setEndValue(QPointF(pos2.x(),pos1.y()));
    anime1->start(QAbstractAnimation::DeleteWhenStopped);

    //动画2
    QPropertyAnimation *anime2=new QPropertyAnimation(destination,"pos");
    anime2->setDuration(duration);
    anime2->setStartValue(pos2);
    anime2->setEndValue(QPointF(pos1.x(),pos2.y()));
    anime2->start(QAbstractAnimation::DeleteWhenStopped);

    //启动两个动画.该函数启动时不阻塞,移动动画自动执行
    anime1->start();
    anime2->start();
    connect(anime2,&QPropertyAnimation::finished,this,[=](){
        //动画结束后操作
        allRect[swapping1]->setBrush(Qt::white);
        allRect[swapping2]->setBrush(Qt::white);
        std::swap(allRect[swapping1],allRect[swapping2]);
        //对对应的线程发出执行下一步的请求
        if(withdrawing){
            withdrawSortObj->tryNextStepSort();
        }else{
            sortObj->tryNextStepSort();
        }
    });
    swapCount++;
    emit dataUpdate(sortObj->timeCost);
    return;
}


//比较函数,效果上相当于返回sample[i]<sample[j].在编写排序算法时,进行样本间比较请使用该函数.
void BaseCanva::animatedCmp(int i, int j)
{
    allRect[lastI]->setBrush(Qt::white);
    allRect[lastJ]->setBrush(Qt::white);
    lastI=i;
    lastJ=j;
    if(!withdrawing){
        //如果不是在撤回,记录操作
        withdrawSortObj->executedIsSwap.push_back(false);
        withdrawSortObj->executedInfo.push_back(std::make_pair(i,j));
    }
    allRect[i]->setBrush(QColor(0x33ccff));
    allRect[j]->setBrush(QColor(0x33ccff));
    QEventLoop loop;
    QTimer::singleShot(interval, &loop, &QEventLoop::quit);
    loop.exec();
    if(withdrawing){
        withdrawSortObj->tryNextStepSort();
    }else{
        sortObj->tryNextStepSort();
    }
    cmpCount++;
    emit dataUpdate(sortObj->timeCost);
    return;
}


//强制赋值动画,为非原地排序算法而准备
void BaseCanva::animatedAssign(int i)
{
    if(i == -1){
        assignCount++;
        QEventLoop loop;
        QTimer::singleShot(interval, &loop, &QEventLoop::quit);
        loop.exec();
        emit dataUpdate(sortObj->timeCost);
        sortObj->tryNextStepSort();
        return;
    }
    allRect[lastI]->setBrush(Qt::white);
    allRect[lastJ]->setBrush(Qt::white);
    lastI = lastJ = i;
    allRect[i]->setBrush(QColor(0x33ccff));

    //画布大小参数
    const int width=this->width();
    const int height=this->height();

    //以下是计算获得的每个长方体的大小参数
    const double averageWidth=width/(double)cap;
    const double heightWeight=(height-topSpace)/(double)maxDifference;

    double newHeight = heightWeight*sample->at(i);
    allRect[i]->setRect(0, 0, averageWidth, newHeight);
    allRect[i]->setPos(leftSpace + averageWidth * i, height - bottomSpace - newHeight);

    QEventLoop loop;
    QTimer::singleShot(interval, &loop, &QEventLoop::quit);
    loop.exec();

    assignCount++;
    emit dataUpdate(sortObj->timeCost);

    sortObj->tryNextStepSort();
    return;
}


//在排序完成后调用该函数,将已经排序完成的样本标成绿色.
void BaseCanva::completeMark()
{
    SortCompleteThread* temp = new SortCompleteThread(cap,&allRect,lastI,lastJ);
    completeThread = temp;
    connect(temp, &QThread::finished, temp, &QObject::deleteLater);
    connect(temp,&SortCompleteThread::updateRequest,this,[=]{
        viewport()->update();
    });
    connect(temp,&SortCompleteThread::finished,this,[=]{
        emit finished();
    });
    temp->start();
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
    arr->at(lastI)->setBrush(Qt::white);
    arr->at(lastJ)->setBrush(Qt::white);

    for(int i=0;i<cap;i++){
        if(isInterruptionRequested())
            return;
        arr->at(i)->setBrush(Qt::green);
        QThread::usleep(1);
        emit updateRequest();
    }
    return;
}


//////////////////////////
/// \brief SortObject类
void SortObject::swapping(int i, int j)
{
    if(i==j)return;
    emit swapSignal(i,j);
    std::swap(sample->at(i),sample->at(j));
    pause();
    return;
}


bool SortObject::comparing(int i, int j)
{
    emit cmpSignal(i,j);
    pause();
    return true;
}

void SortObject::assigning(int i)
{
    emit assignSignal(i);
    pause();
    return;
}


void SortObject::pause()
{
    mutex.lock();
    timeCost = timer.elapsed();
    if(!interruptRequested){
        condition.wait(&mutex);
    }
    mutex.unlock();
    return;
}


void SortObject::setSingleStepMode()
{
    mutex.lock();
    singleStepMode = true;
    mutex.unlock();
    return;
}


void SortObject::tryNextStepSort()
{
    mutex.lock();
    if(!singleStepMode)
        condition.wakeAll();
    mutex.unlock();
    return;
}

void SortObject::interruptRequest()
{
    interruptRequested = true;
    return;
}


void SortObject::resumeSort()
{
    mutex.lock();
    singleStepMode = false;
    condition.wakeAll();
    mutex.unlock();
    return;
}

void SortObject::forceNextStepSort()
{
    mutex.lock();
    condition.wakeAll();
    mutex.unlock();
    return;
}


SortObject::SortObject(int type,std::vector<int>* sampIn,QObject *parent)
    : QObject{parent}
    , sample(sampIn)
    , type(type)
{}


void WithdrawSort::sort()
{
    isSorting = true;
    pause();
    while((!interruptRequested)&&(!withdrawedIsSwap.empty())){
        if(withdrawedIsSwap.back()){
            swapping(withdrawedInfo.back().first,withdrawedInfo.back().second);
        }else{
            comparing(withdrawedInfo.back().first,withdrawedInfo.back().second);
        }
        withdrawedInfo.pop_back();
        withdrawedIsSwap.pop_back();
    }
    normal = withdrawedIsSwap.empty();
    //如果处于连续排序状态,而且撤回列表已经清空,则发出正常信号激活正排序线程
    if(normal&&!singleStepMode)
        emit normalized();
    interruptRequested = false;
    isSorting = false;
    return;
}

void WithdrawSort::withdraw()
{
    isWithdrawing = true;
    while((!interruptRequested)&&(!executedIsSwap.empty())){
        if(executedIsSwap.back()){
            swapping(executedInfo.back().first,executedInfo.back().second);
        }else{
            comparing(executedInfo.back().first,executedInfo.back().second);
        }
        executedInfo.pop_back();
        executedIsSwap.pop_back();
    }
    normal = withdrawedIsSwap.empty();
    interruptRequested = false;
    isWithdrawing = false;
    return;
}
