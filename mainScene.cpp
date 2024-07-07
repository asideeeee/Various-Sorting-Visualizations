#include "mainScene.h"
#include "./ui_mainScene.h"
#include"singlechoosescene.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(960,540);
    ui->option_comboBox->addItem("960×540");
    ui->option_comboBox->addItem(("640×360"));
    ui->option_comboBox->addItem(("1280×720"));
    connect(ui->option_comboBox,&QComboBox::activated,[=](int index){
        if(index==0)
            setFixedSize(960,540);
        else if(index==1)
            setFixedSize(640,1360);
        else
            setFixedSize(1280,720);
    });
    connect(ui->singleSortBtn,&QPushButton::clicked,[=](){
        chooseScene=new singleChooseScene(this);
    });
}

Widget::~Widget()
{
    delete ui;
}
