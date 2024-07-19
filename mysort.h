#ifndef MYSORT_H
#define MYSORT_H

#include <QObject>
#include<vector>
#include<QThread>
#include<stack>
class Mysort : public QObject
{
    Q_OBJECT
public:
    explicit Mysort(QObject *parent = nullptr);
    void work(std::vector<int>sort_numbers,int i,int speed);
public:
    //冒泡排序
    void bubble(std::vector<int>&arr,int a);
    //选择排序
    void select(std::vector<int>&arr,int a);
    //堆排序
    void heapSort(std::vector<int>&arr,int a);
    //直接插入排序
    void inserySort(std::vector<int>&arr,int a);
    //希尔排序
    void shellSort(std::vector<int>&arr,int a);
    //归并排序
    void mergeSort(std::vector<int>&arr,int a);
    //基数排序
    void radixSort(std::vector<int>&arr,int a);
    //快速排序
    //参数类型：数组，左指针，右指针，速度，比较次数，改变次数
    void quickSort(std::vector<int>&arrr,int speed);
    //交换
    void swap(int i,int j,std::vector<int>&arr);
private:
    int update_time=0;
    //在单一线程中要用引用
    void heapify(std::vector<int>&arr,int n,int i ,int &ct,int &st,int &sp);
    //快排辅助数组;后三个参数一个意思
    int partSort(std::vector<int>&arr,int left,int right,int speed,int &cmp,int&swp);
    //基数排序辅助函数
    void countingSort(std::vector<int>&arr,int exp,int speed,int &cmptime,int &swaptime);
    bool sorted=0;
signals:
    //结束信号:
    void send_end();
    //发送交换和比较信号；
    void sent_cmp(int n);
    void sent_swap(int n);
    void sent_update(int n);
    //发送交换柱子的信号
    void swap_columns(int i,int j,std::vector<int>a);
    //发送修改柱子的信号
    void change_columns(int i,int tar,bool how);
    //发送改变柱子的颜色，交换柱子，同时在比较完了后要换回来
    void change_color_swap(int i,int j,bool change);
};

#endif // MYSORT_H
