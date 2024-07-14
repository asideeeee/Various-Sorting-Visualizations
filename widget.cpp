#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置窗口大小
    this->setFixedSize(900,740);
    //添加数据量
    ui->cBox_num->addItem("10");
    ui->cBox_num->addItem("20");
    ui->cBox_num->addItem("50");
    ui->cBox_num->addItem("100");
    ui->cBox_num->addItem("150");
    ui->cBox_num->addItem("200");
    ui->cBox_num->setCurrentIndex(0);
    //计时器
    timer=new QTimer(this);
    timer->setInterval(20);
    connect(timer,&QTimer::timeout,[=](){
        time_cost++;
        double temptime=((double)time_cost)/50;
        ui->first_time->setText("用时"+QString::number(temptime)+"秒");
    });
    connect(ui->cBox_num,&QComboBox::activated,[=](){
        isSorting=false;
        num=ui->cBox_num->currentText().toInt();
    });
    //生成新数据
    connect(ui->btn_new,&QPushButton::clicked,this,generateData);
    //显示生成数据
    connect(ui->btn_showData,&QPushButton::clicked,this,generateColumns);

    //排序速度
    ui->cBox_sortSpeed->addItem("迅速");
    ui->cBox_sortSpeed->addItem("快");
    ui->cBox_sortSpeed->addItem("中");
    ui->cBox_sortSpeed->addItem("慢");
    ui->cBox_sortSpeed->setCurrentIndex(2);
    connect(ui->cBox_sortSpeed,&QComboBox::activated,[=](){
        //如果正在排序的话设置是没用的
        if(isSorting==false)
        {
            //这是根据之前的50来设置的，可以调整（或者说根据数据量）
            speed=(ui->cBox_sortSpeed->currentIndex()+1)*20;
        }
    });

    //设置排序索引
    connect(ui->cBox_firstAlo,&QComboBox::activated,[=](){
        index_alogrithm_first=ui->cBox_firstAlo->currentIndex();
    });
    connect(ui->cBox_secondAlgo,&QComboBox::activated,[=](){
        index_alogrithm_second=ui->cBox_secondAlgo->currentIndex();
    });

    ui->cBox_firstAlo->addItem("冒泡排序");
    ui->cBox_firstAlo->addItem("选择排序");
    ui->cBox_firstAlo->setCurrentIndex(0);

    ui->cBox_secondAlgo->addItem("冒泡排序");
    ui->cBox_secondAlgo->addItem("选择排序");
    ui->cBox_secondAlgo->setCurrentIndex(0);

    //以下两行代码进行的行为描述:
    //创建两个继承于QThread的类,也就是说创建了两个独立运行的线程,用于同时展示两种排序
    sort_Alogrithm*temp1=new sort_Alogrithm(this);
    second_sort*temp2=new second_sort(this);

    //当排序按钮按下后处于排序状态
    connect(ui->btn_showData,&QPushButton::clicked,[=](){
        isSorting=true;
    });
    //按下排序按钮启动子线程，不过按理来说排序结束后子线程应该被销毁
    //如果没有数组以及数据框，弹出警告框并返回
    connect(ui->btn_sort,&QPushButton::clicked,[=](){
       if(num==0){QMessageBox::critical(this, "错误信息", "没有选择数据量");return;}
       if(numbers.isEmpty()){QMessageBox::critical(this, "错误信息", "没有生成数组");return;}
       if(columns_first.isEmpty()){QMessageBox::critical(this, "错误信息", "没有生成数据图像");return;}
       if(index_alogrithm_first<0){QMessageBox::critical(this, "错误信息", "没有选择合法的排序算法");return;}
        if(num!=0&&!columns_first.isEmpty())
            {
            time_cost=0;
            timer->start();
            emit temp1->recInformation(index_alogrithm_first,speed,numbers);
            temp1->start();
        }
    });
    connect(temp1,&sort_Alogrithm::finished,[this](){
        timer->stop();
    });
    //先把线程2注释掉
    connect(ui->btn_sort,&QPushButton::clicked,[=](){
        if(num==0){QMessageBox::critical(this, "错误信息", "没有选择数据量");return;}
        if(numbers.isEmpty()){QMessageBox::critical(this, "错误信息", "没有生成数组");return;}
        if(columns_second.isEmpty()){QMessageBox::critical(this, "错误信息", "没有生成数据图像");return;}
        if(index_alogrithm_second<0){QMessageBox::critical(this, "错误信息", "没有选择合法的排序算法");return;}
        if(num!=0&&!columns_second.isEmpty())
        {
            //用户的设置通过了参数合法性检验.
            //以下代码依次调用了关键信息设置函数,和线程启动函数
            emit temp2->recInformation(index_alogrithm_second,speed,numbers);
            temp2->start();
        }
    });
    connect(temp1,&sort_Alogrithm::send_cmp,[=](int x){
        ui->first_cmp->setText("比较次数："+QString::number(x));
    });
    connect(temp1,&sort_Alogrithm::send_swap,[=](int x){
        ui->first_swap->setText("交换次数："+QString::number(x));
    });

    connect(temp2,&second_sort::send_cmp,[=](int x){
        ui->second_cmp->setText("比较次数："+QString::number(x));
    });
    connect(temp2,&second_sort::send_swap,[=](int x){
        ui->second_swap->setText("交换次数："+QString::number(x));
    });
    connect(temp1,&sort_Alogrithm::Al_swap_columns,this,&Widget::swapColumns_first);
    connect(temp1,&sort_Alogrithm::Al_swap_columns,this,&Widget::updateColumns_first);
    connect(temp2,&second_sort::Al_swap_columns,this,&Widget::swapColumns_second);
    connect(temp2,&second_sort::Al_swap_columns,this,&Widget::updateColumns_second);
}

//创建样本函数.
void Widget:: generateData(){
    if(num==0){QMessageBox::critical(this, "错误信息", "没有选择数据量");return;}
    //如果数组不为空需要清除之前数组
    if(!numbers.isEmpty()){numbers.clear();}
    for(int i=0;i<num;i++)
    {
        //添加随机数，范围可调整
        numbers.append(QRandomGenerator::global()->bounded(1,num*2));
    }
}
void Widget:: generateColumns(){
    //如果此时数组为空则弹出警告对话框，并要求添加数字
    if(numbers.isEmpty()){QMessageBox::critical(this, "错误信息", "没有生成数组");return;}
    //对比的数据框的显示
    if(!columns_first.isEmpty())
    {
        for(int i=0;i<columns_first.size();i++)
        {
            ui->hLayout_first->removeWidget(columns_first[i]);
            delete columns_first[i];
        }
       columns_first.clear();
    }
    if(!columns_second.isEmpty())
    {
        for(int i=0;i<columns_second.size();i++)
        {
            ui->hLayout_second->removeWidget(columns_second[i]);
            delete columns_second[i];
        }
        columns_second.clear();
    }
    for(int i=0;i<num;i++)
    {
        columns_first.append(new QLabel());
        double columns_Width=double(ui->Hwidget_first->width())/(double(num)*1.2);
        double columns_Height=double(ui->Hwidget_first->height())*double(numbers[i])*0.9/(num*2);
        ui->hLayout_first->addWidget(columns_first[i],0,Qt::AlignBottom);
        columns_first[i]->setFixedHeight(columns_Height);
        columns_first[i]->setFixedWidth(columns_Width);
        columns_first[i]->setStyleSheet("background-color: blue;"
                                  "border-radius: 1px;");
        columns_first[i]->setVisible(true);
    }
    for(int i=0;i<num;i++)
    {
        columns_second.append(new QLabel());
        double columns_Width=double(ui->Hwidget_second->width())/(double(num)*1.2);
        double columns_Height=double(ui->Hwidget_second->height())*double(numbers[i])*0.9/(num*2);
        ui->hLayout_second->addWidget(columns_second[i],0,Qt::AlignBottom);
        columns_second[i]->setFixedHeight(columns_Height);
        columns_second[i]->setFixedWidth(columns_Width);
        columns_second[i]->setStyleSheet("background-color: green;"
                                  "border-radius: 1px;");
        columns_second[i]->setVisible(true);
    }
}

void Widget:: swapColumns_first(int i,int j,QVector<int>numbers){
    double h1=double(ui->Hwidget_first->height())*double(numbers[i])*0.9/(num*2);
    double h2=double(ui->Hwidget_first->height())*double(numbers[j])*0.9/(num*2);
    columns_first[i]->setFixedHeight(h2);
    columns_first[j]->setFixedHeight(h1);
    //qDebug()<<"temp1交换元素";
}
void Widget:: swapColumns_second(int i,int j,QVector<int>numbers){
    double h1=double(ui->Hwidget_second->height())*double(numbers[i])*0.9/(num*2);
    double h2=double(ui->Hwidget_second->height())*double(numbers[j])*0.9/(num*2);
    columns_second[i]->setFixedHeight(h2);
    columns_second[j]->setFixedHeight(h1);
    //qDebug()<<"temp2交换元素";
}
void Widget:: updateColumns_first(int i,int j,QVector<int>numbers){
    double h=double(ui->Hwidget_first->height())*double(j)*0.9/(num*2);
    columns_first[i]->setFixedHeight(h);
}
void Widget:: updateColumns_second(int i,int j,QVector<int>numbers){
    double h=double(ui->Hwidget_second->height())*double(j)*0.9/(num*2);
    columns_second[i]->setFixedHeight(h);
}
Widget::~Widget()
{
    delete ui;
}
