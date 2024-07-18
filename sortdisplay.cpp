#include "sortdisplay.h"
#include "ui_sortdisplay.h"
#include <QDebug>


SortDisplay::SortDisplay(QWidget* prev,std::vector<int>* sampIn,SortObject* sortObjIn,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SortDisplay)
    , previous(prev)
{
    ui->setupUi(this);
    this->setWindowTitle("排序可视化界面");
    resize(1920,1080);
    sortThread = new QThread();
    withdrawThread = new QThread();
    WithdrawSort* withdrawer = new WithdrawSort(sortObjIn->sample);


    //初始化画布数据
    ui->baseCanva->sample=sampIn;
    ui->baseCanva->sortObj=sortObjIn;
    ui->baseCanva->withdrawSortObj=withdrawer;
    ui->baseCanva->initializeRect();
    ui->baseCanva->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->baseCanva->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //初始化动画速度
    ui->speedSpinBox->setValue(1);

    //连接排序算法与动画函数
    connect(sortObjIn,&SortObject::swapSignal,ui->baseCanva,&BaseCanva::animatedSwap);
    connect(sortObjIn,&SortObject::cmpSignal,ui->baseCanva,&BaseCanva::animatedCmp);
    connect(sortObjIn,&SortObject::completeSignal,ui->baseCanva,&BaseCanva::completeMark);
    connect(sortObjIn,&SortObject::assignSignal,ui->baseCanva,&BaseCanva::animatedAssign);
    connect(ui->baseCanva,&BaseCanva::finished,this,&SortDisplay::disableAllBtn);

    connect(withdrawer,&SortObject::swapSignal,ui->baseCanva,&BaseCanva::animatedSwap);
    connect(withdrawer,&SortObject::cmpSignal,ui->baseCanva,&BaseCanva::animatedCmp);

    //将排序逻辑转移至另外的线程,本GUI线程只负责动画

    withdrawer->moveToThread(withdrawThread);
    sortObjIn->moveToThread(sortThread);
    connect(sortThread, &QThread::finished, sortThread, &QThread::deleteLater);

    //将线程的启动信号和对应的排序对象管辖的排序函数逻辑相连
    connect(sortThread,&QThread::started,sortObjIn,&SortObject::sort);
    connect(this,&SortDisplay::beginWithdraw, withdrawer,&WithdrawSort::withdraw);
    connect(this,&SortDisplay::beginWithdrawerSort, withdrawer,&WithdrawSort::sort);

    //将撤回线程的正常化信号(即撤回列表清空信号)连接到排序线程的开始排序信号
    connect(withdrawer, &WithdrawSort::normalized,ui->baseCanva,[=](){
        ui->baseCanva->withdrawing = false;
        ui->baseCanva->sortObj->resumeSort();
    });

    //启动后台线程,后台线程此时将会进入排序函数的逻辑中,并在默认参数下立即暂停等待唤醒函数调用
    sortThread->start();
    //withdrawThread->start();

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
    default:
        break;
    }

    ui->startWithdrawButton->setDisabled(true);
    ui->pauseButton->setDisabled(true);
    ui->withdrawButton->setDisabled(true);

    ui->withdrawButton->hide();
    ui->startWithdrawButton->hide();
    //连接测试信号与线程调试信号
    //connect(this,&SortDisplay::testSig,ui->baseCanva->sortObj,&SortObject::testThreadId);
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
    this->setFixedSize(this->size());

    ui->speedSpinBox->setDisabled(true);
    ui->startWithdrawButton->setDisabled(true);
    ui->withdrawButton->setDisabled(true);
    ui->nextButton->setDisabled(true);
    ui->pauseButton->setDisabled(true);
    ui->startButton->setDisabled(true);

    //主功能开始

    //如果当前撤回线程处于排序函数内部,中断当前撤回线程的排序函数
    if(ui->baseCanva->withdrawSortObj->isSorting){
        ui->baseCanva->withdrawSortObj->interruptRequest();
        ui->baseCanva->withdrawSortObj->forceNextStepSort();
    }
    //如果线程还未进入撤回函数,先通过信号在撤回线程内启动函数
    if(!ui->baseCanva->withdrawSortObj->isWithdrawing){
        ui->baseCanva->withdrawing = true;
        emit beginWithdraw();
    }
    //此时撤回线程已经位于撤回函数内部,强制下步
    ui->baseCanva->withdrawSortObj->forceNextStepSort();
    //主功能结束

    ui->speedSpinBox->setDisabled(false);
    ui->startWithdrawButton->setDisabled(false);
    ui->withdrawButton->setDisabled(false);
    ui->nextButton->setDisabled(false);
    ui->pauseButton->setDisabled(true);
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
    ui->startWithdrawButton->setDisabled(true);
    ui->withdrawButton->setDisabled(true);
    ui->nextButton->setDisabled(true);
    ui->pauseButton->setDisabled(true);
    ui->startButton->setDisabled(true);

    //根据画布表明当前主操作权是否在撤回线程,进行相应的强制下步操作
    if(ui->baseCanva->withdrawing){
        ui->baseCanva->withdrawSortObj->forceNextStepSort();
    }else{
        ui->baseCanva->sortObj->forceNextStepSort();
    }

    ui->speedSpinBox->setDisabled(false);
    ui->startWithdrawButton->setDisabled(false);
    ui->withdrawButton->setDisabled(false);
    ui->nextButton->setDisabled(false);
    ui->startButton->setDisabled(false);

    this->setMinimumSize(QSize(0, 0));
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);

    return;
}


void SortDisplay::on_pauseButton_released()
{
    //根据画布表明是否正在撤回,决定将哪个线程设为单步模式
    if(ui->baseCanva->withdrawing){
        ui->baseCanva->withdrawSortObj->setSingleStepMode();
    }else{
        ui->baseCanva->sortObj->setSingleStepMode();
    }

    this->setMinimumSize(QSize(0, 0));
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);

    ui->speedSpinBox->setDisabled(false);
    ui->startWithdrawButton->setDisabled(false);
    ui->withdrawButton->setDisabled(false);
    ui->nextButton->setDisabled(false);
    ui->pauseButton->setDisabled(true);
    ui->startButton->setDisabled(false);

    return;
}


void SortDisplay::on_startButton_released()
{
    //排序期间禁止使用的窗口操作
    this->setFixedSize(this->size());

    ui->speedSpinBox->setDisabled(true);
    ui->startWithdrawButton->setDisabled(true);
    ui->withdrawButton->setDisabled(true);
    ui->nextButton->setDisabled(true);
    ui->pauseButton->setDisabled(false);
    ui->startButton->setDisabled(true);

    ui->pauseButton->setText("暂停排序");
    //排序启动
    //如果画布表明正在撤回,则启动撤回线程的排序函数
    if(ui->baseCanva->withdrawing){
        //中断任何当前函数
        ui->baseCanva->withdrawSortObj->interruptRequest();
        ui->baseCanva->withdrawSortObj->forceNextStepSort();
        //通过信号在排序线程内启动其排序函数
        emit beginWithdrawerSort();
        ui->baseCanva->withdrawSortObj->resumeSort();
    }else{
        //否则,直接启动主排序线程的排序函数即可
        ui->baseCanva->sortObj->resumeSort();
    }

    return;
}


//禁用所有按钮
void SortDisplay::disableAllBtn()
{
    ui->speedSpinBox->setDisabled(true);
    ui->startWithdrawButton->setDisabled(true);
    ui->withdrawButton->setDisabled(true);
    ui->nextButton->setDisabled(true);
    ui->pauseButton->setDisabled(true);
    ui->startButton->setDisabled(true);
    this->setMinimumSize(QSize(0, 0));
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);

    return;
}


void SortDisplay::on_startWithdrawButton_released()
{
    //连续撤回期间禁止使用的窗口操作
    this->setFixedSize(this->size());

    ui->speedSpinBox->setDisabled(true);
    ui->startWithdrawButton->setDisabled(true);
    ui->withdrawButton->setDisabled(true);
    ui->nextButton->setDisabled(true);
    ui->pauseButton->setDisabled(false);
    ui->startButton->setDisabled(true);

    ui->pauseButton->setText("暂停撤回");
    //连续撤回启动
    //中断当前撤回线程的排序函数
    if(ui->baseCanva->withdrawSortObj->isSorting){
        ui->baseCanva->withdrawSortObj->interruptRequest();
        ui->baseCanva->withdrawSortObj->forceNextStepSort();
    }
    //如果线程还未进入撤回函数,先通过信号在撤回线程内启动函数
    if(!ui->baseCanva->withdrawSortObj->isWithdrawing){
        ui->baseCanva->withdrawing = true;
        emit beginWithdraw();
    }
    //此时线程必然正在撤回函数内的暂停位点
    //随后启动连续撤回函数,脱离暂停
    ui->baseCanva->withdrawSortObj->resumeSort();

    return;
}


