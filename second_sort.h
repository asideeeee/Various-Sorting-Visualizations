#ifndef SECOND_SORT_H
#define SECOND_SORT_H

#include <QObject>
#include<QThread>
#include<QVector>

class second_sort : public QThread
{
    Q_OBJECT
public:
    explicit second_sort(QObject *parent = nullptr);
    //冒泡排序
    void bubble();
    //选择排序
    void select();
    //交换,数组中的元素
    void swap(int i,int j);
    void update_time();
signals:
    //传递信号：
    //比较次数
    void send_cmp(int num);
    //交换次数
    void send_swap(int num);
    //交换柱子的值
    void Al_swap_columns(int i,int j,QVector<int>a);
    //改变柱子的值
    void Al_change_columns(int i,int target,QVector<int>a);
protected:
    void run() override;
public slots:
    //接受主线程传递的信息
    void recInformation(int index,int speed,QVector<int>arr);

private:
    //算法索引
    int Alogrithm_index;

    int c_speed;//排序速度

    //排序数组
    QVector<int>sort_numbers;
    //排序的相关参数
    int cmp=0;
    int swp=0;
};

#endif // SECOND_SORT_H
