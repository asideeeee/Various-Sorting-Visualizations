#include "singlechoosescene.h"
#include"setcase.h"
#include "ui_singlechoosescene.h"


singleChooseScene::singleChooseScene(int wigetMultiplier,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::singleChooseScene)
{
    setFixedSize(320*wigetMultiplier,180*wigetMultiplier);
    ui->setupUi(this);
    //给每个排序选择按钮安排信号槽，跳转到相应的页面
    connect(ui->sortButton1,&QPushButton::clicked,this,[=](){
        setCase* setcase=new setCase(1,wigetMultiplier);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
    connect(ui->sortButton2,&QPushButton::clicked,this,[=](){
        setCase* setcase=new setCase(2,wigetMultiplier);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
    connect(ui->sortButton3,&QPushButton::clicked,this,[=](){
        setCase* setcase=new setCase(3,wigetMultiplier);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
    connect(ui->sortButton4,&QPushButton::clicked,this,[=](){
        setCase* setcase=new setCase(4,wigetMultiplier);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
    connect(ui->sortButton5,&QPushButton::clicked,this,[=](){
        setCase* setcase=new setCase(5,wigetMultiplier);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
    connect(ui->sortButton6,&QPushButton::clicked,this,[=](){
        setCase* setcase=new setCase(6,wigetMultiplier);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
    connect(ui->sortButton7,&QPushButton::clicked,this,[=](){
        setCase* setcase=new setCase(7,wigetMultiplier);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
    connect(ui->sortButton8,&QPushButton::clicked,this,[=](){
        setCase* setcase=new setCase(8,wigetMultiplier);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
    connect(ui->sortButton9,&QPushButton::clicked,this,[=](){
        setCase* setcase=new setCase(9,wigetMultiplier);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
    connect(ui->sortButton10,&QPushButton::clicked,this,[=](){
        setCase* setcase=new setCase(10,wigetMultiplier);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
}

singleChooseScene::~singleChooseScene()
{
    delete ui;
}
