#include "sortdisplay.h"
#include "ui_sortdisplay.h"
#include <QDebug>


SortDisplay::SortDisplay(QWidget* prev,std::vector<int>* sampIn,SortObject* sortObjIn,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SortDisplay)
    , previous(prev)
{
    ui->setupUi(this);
    resize(1920,1080);
    sortThread = new QThread();

    //初始化画布数据
    ui->baseCanva->sample=sampIn;
    ui->baseCanva->sortObj=sortObjIn;
    ui->baseCanva->initializeRect();
    ui->baseCanva->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->baseCanva->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //初始化动画速度
    ui->speedSpinBox->setValue(60);

    //连接排序算法与动画函数
    connect(sortObjIn,&SortObject::swapSignal,ui->baseCanva,&BaseCanva::animatedSwap);
    connect(sortObjIn,&SortObject::cmpSignal,ui->baseCanva,&BaseCanva::animatedCmp);
    connect(sortObjIn,&SortObject::completeSignal,ui->baseCanva,&BaseCanva::completeMark);

    //将排序逻辑转移至另外的线程,本GUI线程只负责动画

    sortObjIn->moveToThread(sortThread);
    connect(sortThread, &QThread::finished, sortThread, &QThread::deleteLater);

    //将线程的启动信号和对应的排序对象管辖的排序函数逻辑相连
    connect(sortThread,&QThread::started,sortObjIn,&SortObject::sort);

    //启动后台线程,后台线程此时将会进入排序函数的逻辑中,并在默认参数下立即暂停等待唤醒函数调用
    sortThread->start();

    //连接测试信号与线程调试信号
    connect(this,&SortDisplay::testSig,ui->baseCanva->sortObj,&SortObject::testThreadId);
}

SortDisplay::~SortDisplay()
{
    if(sortThread)
    {
        ui->baseCanva->sortObj->interruptRequest();
        sortThread->quit();
        ui->baseCanva->sortObj->resumeSort();
        sortThread->wait();
    }
    delete ui;
}

BaseCanva *SortDisplay::getCanva()
{
    return ui->baseCanva;
}

Ui::SortDisplay *SortDisplay::getSortDisplayUi()
{
    return ui;
}


//退出展示页面函数
void SortDisplay::on_exitButton_released()
{
    previous->show();
    emit displayWindowClosed();
    this->close();
    return;
}


//要是时间不够难度太大就删掉这个功能吧
void SortDisplay::on_withdrawButton_released()
{

}


//动画速度设置
void SortDisplay::on_speedSpinBox_valueChanged(int arg1)
{
    ui->baseCanva->interval=arg1;
    return;
}


void SortDisplay::on_nextButton_released()
{
    ui->baseCanva->sortObj->forceNextStepSort();
    return;
}


void SortDisplay::on_pauseButton_released()
{
    ui->baseCanva->sortObj->setSingleStepMode();
    return;
}


void SortDisplay::on_startButton_released()
{
    ui->baseCanva->sortObj->resumeSort();
    return;
}


/// \Attention
//注意:以下槽函数仅仅在调试时有用
//用于测试一些函数能否正常运行
//正式打包发布前请删除该函数及其对应按钮
/// \Attention
void SortDisplay::on_debugButton_released()
{
    qDebug()<<"Main Thread's id is"<<QThread::currentThreadId();
    qDebug()<<"sending signal.";
    emit testSig();
    qDebug()<<"directly executing slot";
    ui->baseCanva->sortObj->testThreadId();
    //ui->baseCanva->animatedSwap(0,1);
    return;
}


