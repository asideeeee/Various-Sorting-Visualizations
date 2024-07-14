#include "sortdisplay.h"
#include "ui_sortdisplay.h"
#include <QDebug>


SortDisplay::SortDisplay(QWidget* prev,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SortDisplay)
    , previous(prev)
{
    ui->setupUi(this);
    resize(1920,1080);
    ui->baseCanva->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->baseCanva->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->speedSpinBox->setValue(60);
    connect(this->ui->pauseButton,&QPushButton::released,this->ui->baseCanva->sortObj,&SortObject::setPause);
    connect(this->ui->startButton,&QPushButton::released,this->ui->baseCanva->sortObj,&SortObject::startSort);
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


void SortDisplay::on_nextButton_released()
{

}


void SortDisplay::on_withdrawButton_released()
{

}


void SortDisplay::on_speedSpinBox_valueChanged(int arg1)
{
    ui->baseCanva->interval=arg1;
    return;
}

/// \Attention
//注意:以下槽函数仅仅在调试时有用
//用于测试一些函数能否正常运行
//正式打包发布前请删除该函数及其对应按钮
/// \Attention
void SortDisplay::on_debugButton_released()
{
    qDebug()<<"已收到动画展示要求";
    ui->baseCanva->completeMark();
    return;
}

