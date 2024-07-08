#include "mainScene.h"
#include "./ui_mainScene.h"
#include"singlechoosescene.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setFixedSize(960,540);
    ui->option_comboBox->addItem(("640×360"));
    ui->option_comboBox->addItem("960×540");
    ui->option_comboBox->addItem(("1280×720"));
    ui->option_comboBox->setCurrentIndex((1));
    connect(ui->option_comboBox,&QComboBox::activated,this,[=](int index){
        wigetMultiplier=index+2;
        setFixedSize(320*wigetMultiplier,180*wigetMultiplier);
    });
    connect(ui->singleSortBtn,&QPushButton::clicked,this,[=](){
        chooseScene=new singleChooseScene(wigetMultiplier,nullptr);
        chooseScene->setAttribute(Qt::WA_DeleteOnClose);
        this->hide();
        chooseScene->show();
    });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::receiveSample(std::vector<int>& arr){

}
