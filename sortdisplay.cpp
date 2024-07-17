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
    connect(ui->baseCanva,&BaseCanva::finished,this,[=](){
        this->setMinimumSize(QSize(0, 0));
        this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
        ui->startButton->setDisabled(true);
        ui->pauseButton->setDisabled(true);
    });

    //将排序逻辑转移至另外的线程,本GUI线程只负责动画

    sortObjIn->moveToThread(sortThread);
    connect(sortThread, &QThread::finished, sortThread, &QThread::deleteLater);

    //将线程的启动信号和对应的排序对象管辖的排序函数逻辑相连
    connect(sortThread,&QThread::started,sortObjIn,&SortObject::sort);

    //启动后台线程,后台线程此时将会进入排序函数的逻辑中,并在默认参数下立即暂停等待唤醒函数调用
    sortThread->start();

    switch(sortObjIn->type){
    case 1:ui->sortTypeLabel->setText("直接插入排序");
        break;
    case 2:ui->sortTypeLabel->setText("折半插入排序");
        break;
    case 3:ui->sortTypeLabel->setText("希尔排序");
        break;
    case 4:ui->sortTypeLabel->setText("冒泡排序");
        break;
    case 5:ui->sortTypeLabel->setText("快速排序");
        break;
    case 6:ui->sortTypeLabel->setText("直接选择排序");
        break;
    case 7:ui->sortTypeLabel->setText("堆排序");
        break;
    case 8:ui->sortTypeLabel->setText("树形选择排序");
        break;
    case 9:ui->sortTypeLabel->setText("归并排序");
        break;
    case 10:ui->sortTypeLabel->setText("基数排序");
        break;
    }

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

void SortDisplay::setResizable()
{
    this->setMinimumSize(QSize(0, 0));
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    return;
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
    if(ui->baseCanva->executedIsSwap.empty())return;

    this->setFixedSize(this->size());
    ui->speedSpinBox->setDisabled(true);
    ui->nextButton->setDisabled(true);
    ui->withdrawButton->setDisabled(true);
    ui->startButton->setDisabled(true);

    bool isSwap = ui->baseCanva->executedIsSwap.back();
    ui->baseCanva->executedIsSwap.pop_back();
    std::pair<int,int> info = ui->baseCanva->executedInfo.back();
    ui->baseCanva->executedInfo.pop_back();
    if(isSwap){
        ui->baseCanva->withdrawedIsSwap.push_back(true);

    } else {
        ui->baseCanva->withdrawedIsSwap.push_back(false);
    }
    ui->baseCanva->withdrawedInfo.push_back(info);

    ui->speedSpinBox->setDisabled(false);
    ui->nextButton->setDisabled(false);
    ui->withdrawButton->setDisabled(false);
    ui->startButton->setDisabled(false);
    this->setMinimumSize(QSize(0, 0));
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    return;
}


//动画速度设置
void SortDisplay::on_speedSpinBox_valueChanged(int arg1)
{
    ui->baseCanva->interval=arg1;
    return;
}


void SortDisplay::on_nextButton_released()
{
    this->setFixedSize(this->size());
    ui->speedSpinBox->setDisabled(true);
    ui->nextButton->setDisabled(true);
    ui->withdrawButton->setDisabled(true);
    ui->startButton->setDisabled(true);

    ui->baseCanva->sortObj->forceNextStepSort();

    ui->speedSpinBox->setDisabled(false);
    ui->nextButton->setDisabled(false);
    ui->withdrawButton->setDisabled(false);
    ui->startButton->setDisabled(false);
    this->setMinimumSize(QSize(0, 0));
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    return;
}


void SortDisplay::on_pauseButton_released()
{
    ui->baseCanva->sortObj->setSingleStepMode();
    this->setMinimumSize(QSize(0, 0));
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    ui->speedSpinBox->setDisabled(false);
    ui->nextButton->setDisabled(false);
    ui->withdrawButton->setDisabled(false);
    ui->startButton->setDisabled(false);
    ui->pauseButton->setDisabled(true);
    return;
}


void SortDisplay::on_startButton_released()
{
    //排序期间禁止使用的窗口操作
    this->setFixedSize(this->size());
    ui->pauseButton->setDisabled(false);
    ui->nextButton->setDisabled(true);
    ui->withdrawButton->setDisabled(true);
    ui->startButton->setDisabled(true);
    ui->speedSpinBox->setDisabled(true);
    //排序启动
    ui->baseCanva->sortObj->resumeSort();
    return;
}

void SortDisplay::disableAllBtn()
{
    ui->speedSpinBox->setDisabled(true);
    ui->nextButton->setDisabled(true);
    ui->withdrawButton->setDisabled(true);
    ui->startButton->setDisabled(true);
    ui->pauseButton->setDisabled(true);
    this->setMinimumSize(QSize(0, 0));
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
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


