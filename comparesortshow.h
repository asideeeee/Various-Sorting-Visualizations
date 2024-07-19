#ifndef COMPARESORTSHOW_H
#define COMPARESORTSHOW_H

#include <QWidget>
#include<QTimer>
#include<vector>
#include<QLabel>
#include<QPushButton>
#include<QMessageBox>
#include<QComboBox>
#include<QVector>
#include<QThread>
#include<QSlider>
#include<QPainter>
#include<QIcon>
#include"mysort.h"
namespace Ui {
class compareSortShow;
}

class compareSortShow : public QWidget
{
    Q_OBJECT

public:
    explicit compareSortShow(QWidget*pre,std::vector<int>arr,int index1,int index2,QWidget *parent = nullptr);
    ~compareSortShow();

private:
    Ui::compareSortShow *ui;
    QWidget*previous;
    //算法索引
    int sort_index_first=-1;
    int sort_index_second=-1;
    std::vector<int>arr;
    //柱子数组
    QVector<QLabel*>columns_first;
    QVector<QLabel*>columns_second;

    //计时器与时间,为子线程算计时

    int time1=0;
    int time2=0;
    //速度
    int speed=80;
    int max_num;
    //排序状态
    bool issorting_first=0;
    bool issorting_second=0;
signals:
    void send_information_first(std::vector<int>arr,int index,int speed);
    void send_information_second(std::vector<int>arr,int index,int speed);
public slots:
    //生成柱子
    void generate_columns();
    //交换柱子槽函数
    void swap_columns_first(int i,int j,std::vector<int>a);
    void swap_columns_second(int i,int j,std::vector<int>a);
    //更新柱子槽函数
    void update_columns_first(int index,int tar,bool change);
    void update_columns_second(int index,int tar,bool change);
    //改变柱子颜色
    void change_swap_color_first(int i,int j,bool change);
    void change_swap_color_second(int i,int j,bool change);
    //清除柱子
    void clear_columns();
    //是否启动排序
    void outOfSort();
private slots:
    void on_btn_exit_clicked();
};

#endif // COMPARESORTSHOW_H
