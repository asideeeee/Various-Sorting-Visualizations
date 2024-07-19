#include "comparesortshow.h"
#include "ui_comparesortshow.h"

compareSortShow::compareSortShow(QWidget*pre,std::vector<int>arr,int index1,int index2,QWidget *parent)
    : previous(pre),arr(arr),sort_index_first(index1),sort_index_second(index2),QWidget(parent)
    , ui(new Ui::compareSortShow)
{
    ui->setupUi(this);
    this->setFixedSize(1260,780);
    QThread*thread1=new QThread();
    QThread*thread2=new QThread();
    Mysort*work1=new Mysort;
    Mysort*work2=new Mysort;
    work1->moveToThread(thread1);
    work2->moveToThread(thread2);

    //设置速度条
    ui->speed_change->setRange(20,200);
    ui->speed_change->setValue(50);
    ui->speed_change->setTickPosition(QSlider::TicksBothSides);
    ui->speed_change->setTickInterval(10);
    connect(ui->speed_change,&QSlider::valueChanged,this,[=](int value){
        speed=value;
    });
    //生成图像
    connect(ui->btn_show,&QPushButton::clicked,this,&compareSortShow::generate_columns);
    QTimer*timer1;
    QTimer*timer2;
    //计时器设置
    timer1=new QTimer(this);
    //设置计数间隔
    timer1->setInterval(20);
    //计时器设置
    timer2=new QTimer(this);
    //设置计数间隔
    timer2->setInterval(20);
    connect(timer1,&QTimer::timeout,this,[=](){
        time1++;
        double curtime=double(time1)/50;
        ui->time->setStyleSheet("QLabel { color: black; }");
        ui->time->setText(QString::number(curtime)+"秒");
    });
    connect(timer2,&QTimer::timeout,this,[=](){
        time1++;
        double curtime=double(time1)/50;
        ui->time_2->setStyleSheet("QLabel { color: black; }");
        ui->time_2->setText(QString::number(curtime)+"秒");
    });

    connect(this,&compareSortShow::send_information_first,work1,&Mysort::work);
    connect(ui->btn_begin,&QPushButton::clicked,this,[=](){
        emit send_information_first(arr,sort_index_first,speed);
        //开始时让全部按钮失效
        qDebug()<<"hello"<<sort_index_first;
        ui->btn_show->setEnabled(false);
        ui->btn_begin->setEnabled(false);
        ui->btn_exit->setEnabled(false);
        ui->speed_change->setEnabled(false);
            //排序开始时将其清零；
        issorting_first=1;
        time1=0;
        timer1->start();
        thread1->start();
    });
    //任务结束后计时器停止
    connect(work1,&Mysort::send_end,timer1,&QTimer::stop);
    connect(work1,&Mysort::send_end,this,[=](){
        issorting_first=false;
        //delete work1;
        outOfSort();
    });
    //接收子线程传来的信息：
    //交换柱子
    connect(work1,&Mysort::swap_columns,this,&compareSortShow::swap_columns_first);
    connect(work1,&Mysort::change_columns,this,&compareSortShow::update_columns_first);
    //现在尝试改变柱子的颜色
    connect(work1,&Mysort::change_color_swap,this,&compareSortShow::change_swap_color_first);
    connect(work1,&Mysort::sent_cmp,this,[=](int x){
        ui->cmp->setStyleSheet("QLabel { color: black; }");
        ui->cmp->setText(QString::number(x)+"次");
    });
    connect(work1,&Mysort::sent_swap,this,[=](int x){
        ui->swap->setStyleSheet("QLabel { color: black; }");
        ui->swap->setText(QString::number(x)+"次");
    });
    connect(work1,&Mysort::sent_update,this,[=](int x){
        ui->update->setStyleSheet("QLabel { color: black; }");
        ui->update->setText(QString::number(x)+"次");
    });




    connect(this,&compareSortShow::send_information_second,work2,&Mysort::work);
    connect(ui->btn_begin,&QPushButton::clicked,this,[=](){
        emit send_information_second(arr,sort_index_second,speed);
        qDebug()<<"hello"<<sort_index_second;
        //开始时让全部按钮失效
        ui->btn_show->setEnabled(false);
        ui->btn_begin->setEnabled(false);
        ui->btn_exit->setEnabled(false);
        ui->speed_change->setEnabled(false);
            //排序开始时将其清零；
        issorting_second=1;
        time2=0;
        timer2->start();
        thread2->start();
    });
    //任务结束后计时器停止
    connect(work2,&Mysort::send_end,timer2,&QTimer::stop);
    connect(work2,&Mysort::send_end,this,[=](){
        issorting_second=false;
        //delete work2;
        outOfSort();
    });
    //接收子线程传来的信息：
    //交换柱子
    connect(work2,&Mysort::swap_columns,this,&compareSortShow::swap_columns_second);
    connect(work2,&Mysort::change_columns,this,&compareSortShow::update_columns_second);
    //现在尝试改变柱子的颜色
    connect(work2,&Mysort::change_color_swap,this,&compareSortShow::change_swap_color_second);
    connect(work2,&Mysort::sent_cmp,this,[=](int x){
        ui->cmp_2->setStyleSheet("QLabel { color: black; }");
        ui->cmp_2->setText(QString::number(x)+"次");
    });
    connect(work2,&Mysort::sent_swap,this,[=](int x){
        ui->swap_2->setStyleSheet("QLabel { color: black; }");
        ui->swap_2->setText(QString::number(x)+"次");
    });
    connect(work2,&Mysort::sent_update,this,[=](int x){
        ui->update_2->setStyleSheet("QLabel { color: black; }");
        ui->update_2->setText(QString::number(x)+"次");
    });
}

compareSortShow::~compareSortShow()
{
    delete ui;
}
void compareSortShow::generate_columns(){
    max_num=0;
    for(int i=0;i<arr.size();i++)
    {
        if(arr[i]>max_num)
        {
            max_num=arr[i];
        }
    }
    int num=arr.size();
    for(int i=0;i<num;i++)
    {
        columns_first.append(new QLabel());
        columns_second.append(new QLabel());
        double c_width=double(ui->main_widge1->width())/(1.2*num);
        double c_height=double(arr[i]*ui->main_widge1->height())/double(max_num);
        columns_first[i]->setFixedWidth(c_width);
        columns_first[i]->setFixedHeight(c_height);
        columns_second[i]->setFixedWidth(c_width);
        columns_second[i]->setFixedHeight(c_height);
        ui->h_main_1->addWidget(columns_first[i],0,Qt::AlignBottom);
        ui->h_main_2->addWidget(columns_second[i],0,Qt::AlignBottom);
        //设置柱子的样式表
        columns_first[i]->setStyleSheet("background-color: blue;"
                                        "border-radius: 1px;");
        columns_first[i]->setVisible(true);
        columns_second[i]->setStyleSheet("background-color: yellow;"
                                         "border-radius: 1px;");
        columns_second[i]->setVisible(true);
    }
}
//交换柱子槽函数
void compareSortShow::swap_columns_first(int i,int j,std::vector<int>a){
    int h1=double(a[i]*ui->main_widge1->height())/double(max_num);
    int h2=double(a[j]*ui->main_widge1->height())/double(max_num);
    columns_first[i]->setFixedHeight(h2);
    columns_first[j]->setFixedHeight(h1);
}
void compareSortShow::swap_columns_second(int i,int j,std::vector<int>a){
    int h1=double(a[i]*ui->main_widge2->height())/double(max_num);
    int h2=double(a[j]*ui->main_widge2->height())/double(max_num);
    columns_second[i]->setFixedHeight(h2);
    columns_second[j]->setFixedHeight(h1);
}
//更新柱子槽函数
void compareSortShow::update_columns_first(int index,int tar,bool change){
    if(change)
    {
        columns_first[index]->setStyleSheet("background-color: red;"
                                            "border-radius: 1px;");
    }
    else
    {
        columns_first[index]->setStyleSheet("background-color: blue;"
                                            "border-radius: 1px;");
    }
    int h=double(tar*ui->main_widge1->height())/double(max_num);
    columns_first[index]->setFixedHeight(h);
}
void compareSortShow::update_columns_second(int index,int tar,bool change){
    if(change)
    {
        columns_second[index]->setStyleSheet("background-color: red;"
                                             "border-radius: 1px;");
    }
    else
    {
        columns_second[index]->setStyleSheet("background-color: yellow;"
                                             "border-radius: 1px;");
    }
    int h=double(tar*ui->main_widge2->height())/double(max_num);
    columns_second[index]->setFixedHeight(h);
}
//改变柱子颜色
void compareSortShow::change_swap_color_first(int i,int j,bool change){
    if(change)
    {
        columns_first[i]->setStyleSheet("background-color: black;"
                                        "border-radius: 1px;");
        columns_first[j]->setStyleSheet("background-color: black;"
                                        "border-radius: 1px;");
    }
    else
    {
        columns_first[i]->setStyleSheet("background-color: blue;"
                                        "border-radius: 1px;");
        columns_first[j]->setStyleSheet("background-color: blue;"
                                        "border-radius: 1px;");
    }
}
void compareSortShow::change_swap_color_second(int i,int j,bool change){
    if(change)
    {
        columns_second[i]->setStyleSheet("background-color: black;"
                                         "border-radius: 1px;");
        columns_second[j]->setStyleSheet("background-color: black;"
                                         "border-radius: 1px;");
    }
    else
    {
        columns_second[i]->setStyleSheet("background-color: yellow;"
                                         "border-radius: 1px;");
        columns_second[j]->setStyleSheet("background-color: yellow;"
                                         "border-radius: 1px;");
    }
}
//清除柱子
void compareSortShow::clear_columns(){

}

void compareSortShow::outOfSort(){
    if(!issorting_first&&!issorting_second)
    {
        ui->btn_begin->setEnabled(true);
        ui->btn_show->setEnabled(true);
        ui->btn_exit->setEnabled(true);
        ui->speed_change->setEnabled(true);
    }
}

void compareSortShow::on_btn_exit_clicked()
{
    previous->show();
    this->close();
}

