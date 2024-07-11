#include "mainScene.h"
#include "./ui_mainScene.h"
#include"singlechoosescene.h"
#include"heapsortvisualization.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(1280,720);

    connect(ui->singleSortBtn,&QPushButton::clicked,this,[=](){
        chooseScene=new singleChooseScene(this);
        chooseScene->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        chooseScene->show();
    });
    connect(ui->multySortBtn,&QPushButton::clicked,this,[=](){
        chooseScene=new heapSortVisualization();
        chooseScene->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        chooseScene->show();
    });
}

Widget::~Widget()
{
    delete ui;
}
