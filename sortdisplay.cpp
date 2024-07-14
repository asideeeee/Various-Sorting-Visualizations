#include "sortdisplay.h"
#include "ui_sortdisplay.h"
#include <QDebug>


SortDisplay::SortDisplay(QWidget* prev,std::vector<int>* sampIn,SortObject* sortObjIn,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SortDisplay)
    , previous(prev)
    , sortThread()
{
    ui->setupUi(this);
    resize(1920,1080);

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

    sortObjIn->moveToThread(&sortThread);
    connect(ui->exitButton,&QPushButton::pressed,&sortThread,[=](){
        sortThread.quit();
        sortThread.deleteLater();
    });
    connect(sortObjIn, &SortObject::completeSignal, &sortThread, &QThread::quit);
    connect(&sortThread, &QThread::finished, &sortThread, &QThread::deleteLater);

    connect(&sortThread,&QThread::started,sortObjIn,&SortObject::sort);

    sortThread.start();
}

SortDisplay::~SortDisplay()
{
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


void SortDisplay::on_withdrawButton_released()
{

}


//动画速度设置
void SortDisplay::on_speedSpinBox_valueChanged(int arg1)
{
    ui->baseCanva->interval=arg1-20;
    ui->baseCanva->sortObj->interval=arg1;
    return;
}

/// \Attention
//注意:以下槽函数仅仅在调试时有用
//用于测试一些函数能否正常运行
//正式打包发布前请删除该函数及其对应按钮
/// \Attention
void SortDisplay::on_debugButton_released()
{
    return;
}


void SortDisplay::on_nextButton_released()
{
    ui->baseCanva->sortObj->condition.wakeAll();
    return;
}


void SortDisplay::on_pauseButton_released()
{
    ui->baseCanva->sortObj->singleStepMode = true;
    return;
}


void SortDisplay::on_startButton_released()
{
    ui->baseCanva->sortObj->singleStepMode = false;
    ui->baseCanva->sortObj->condition.wakeAll();
    return;
}

