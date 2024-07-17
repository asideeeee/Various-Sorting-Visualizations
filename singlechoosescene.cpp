#include "singlechoosescene.h"
#include"setcase.h"
#include "ui_singlechoosescene.h"

//此窗口的逻辑编写已完成

singleChooseScene::singleChooseScene(QWidget* prev,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::singleChooseScene)
    , previous(prev)
{
    ui->setupUi(this);
    //给每个排序选择按钮安排信号槽，跳转到相应的页面
    connect(ui->sortButton1,&QPushButton::clicked,this,[=](){
        SetCase* setcase=new SetCase(1,this);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
    connect(ui->sortButton2,&QPushButton::clicked,this,[=](){
        SetCase* setcase=new SetCase(2,this);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
    connect(ui->sortButton3,&QPushButton::clicked,this,[=](){
        SetCase* setcase=new SetCase(3,this);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
    connect(ui->sortButton4,&QPushButton::clicked,this,[=](){
        SetCase* setcase=new SetCase(4,this);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
    connect(ui->sortButton5,&QPushButton::clicked,this,[=](){
        SetCase* setcase=new SetCase(5,this);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
    connect(ui->sortButton6,&QPushButton::clicked,this,[=](){
        SetCase* setcase=new SetCase(6,this);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
    connect(ui->sortButton7,&QPushButton::clicked,this,[=](){
        SetCase* setcase=new SetCase(7,this);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
    connect(ui->sortButton8,&QPushButton::clicked,this,[=](){
        SetCase* setcase=new SetCase(8,this);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
    connect(ui->sortButton9,&QPushButton::clicked,this,[=](){
        SetCase* setcase=new SetCase(9,this);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
    connect(ui->sortButton10,&QPushButton::clicked,this,[=](){
        SetCase* setcase=new SetCase(10,this);
        setcase->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        setcase->show();
    });
    connect(ui->sortButton11, &QPushButton::clicked, this, [=]() {
        sortingScene = new treedata(this);
        this->hide();
        sortingScene->show();
        });
    this->resize(1280,720);
}

singleChooseScene::~singleChooseScene()
{
    delete ui;
}

void singleChooseScene::on_backToMainBtn_released()
{
    previous->show();
    this->close();
}

