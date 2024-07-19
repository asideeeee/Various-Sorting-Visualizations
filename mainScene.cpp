#include "mainScene.h"
#include "./ui_mainScene.h"
#include"singlechoosescene.h"
#include"heapsortvisualization.h"
#include"setcase_second.h"
//此窗口的逻辑编写已完成

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(1280,720);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("主界面");

    connect(ui->singleSortBtn,&QPushButton::clicked,this,[=](){
        chooseScene=new singleChooseScene(this);
        chooseScene->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        chooseScene->show();
    });
    connect(ui->multySortBtn,&QPushButton::clicked,this,[=](){
        //chooseScene=new heapSortVisualization();
        //chooseScene->setAttribute(Qt::WA_DeleteOnClose);
        //this->hide();
        //chooseScene->show();
        //出于测试需要,暂时注释掉
        setcase_second*newScene=new setcase_second(this,nullptr);
        newScene->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        newScene->show();
    });
}

Widget::~Widget()
{
    delete ui;
}
