#include "sortdisplay.h"
#include "ui_sortdisplay.h"


SortDisplay::SortDisplay(QWidget* prev,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SortDisplay)
    , previous(prev)
{
    ui->setupUi(this);
    resize(1920,1080);
    ui->baseCanva->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->baseCanva->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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



void SortDisplay::on_startButton_released()
{

}

