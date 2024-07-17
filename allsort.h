#ifndef ALLSORT_H
#define ALLSORT_H

#include "basecanva.h"

///////////////
//直接插入排序类,编号1
class SimpleInsertSort : public SortObject
{
    Q_OBJECT
public:
    explicit SimpleInsertSort(std::vector<int>* sampIn):
        SortObject(1,sampIn)
    {}

    void InsertSort(std::vector<int>& R,int n);

public slots:
    void sort() override;

};


///////////////
//折半插入排序类,编号2
class HalfInsertSort : public SortObject
{
    Q_OBJECT
public:
    explicit HalfInsertSort(std::vector<int>* sampIn):
        SortObject(2,sampIn)
    {}

    void binaryInsertionSort(std::vector<int>& arr);

public slots:
    void sort() override;

};


///////////////
//希尔排序类,编号3
class ShellSort : public SortObject
{
    Q_OBJECT
public:
    explicit ShellSort(std::vector<int>* sampIn):
        SortObject(3,sampIn)
    {}

    void shellSort(std::vector<int>& arr);

public slots:
    void sort() override;

};


///////////////
//冒泡排序类,编号4
class BubbleSort : public SortObject
{
    Q_OBJECT
public:
    explicit BubbleSort(std::vector<int>* sampIn):
        SortObject(4,sampIn)
    {}

    // 优化后的冒泡排序函数声明
    void optimizedBubbleSort(std::vector<int>& arr);

public slots:
    void sort() override;

};


///////////////
//快速排序类,编号5
class QuickSort : public SortObject
{
    Q_OBJECT
public:
    explicit QuickSort(std::vector<int>* sampIn):
        SortObject(5,sampIn)
    {}

    // 快速排序函数声明
    void quickSort(std::vector<int>& arr, int left, int right);
    // 辅助函数：分区函数
    int partition(std::vector<int>& arr, int left, int right);

public slots:
    void sort() override;

};


//////////////
//直接选择排序类,编号6
class SimpleSelectSort : public SortObject
{
    Q_OBJECT
public:
    explicit SimpleSelectSort(std::vector<int>* sampIn):
        SortObject(6,sampIn)
    {}

    // 直接选择排序函数声明
    void selectionSort(std::vector<int>& arr);

public slots:
    void sort() override;

};

//////////////
//堆排序类,编号7
class HeapSort : public SortObject
{
    Q_OBJECT
public:
    explicit HeapSort(std::vector<int>* sampIn):
        SortObject(7,sampIn)
    {}

    // 堆排序函数声明
    void heapSort(std::vector<int>& arr);
    // 辅助函数：构建最大堆
    void heapify(std::vector<int>& arr, int n, int i);

public slots:
    void sort() override;

};

//////////////
//树形选择排序类,编号8
class TreeSelectSort : public SortObject
{
    Q_OBJECT
public:
    explicit TreeSelectSort(std::vector<int>* sampIn):
        SortObject(8,sampIn)
    {}

    // 树形选择排序函数声明
    void tournamentSort(std::vector<int>& arr);

public slots:
    void sort() override;

};


//////////////
//二路归并排序类,编号9
class MergeSort : public SortObject
{
    Q_OBJECT
public:
    explicit MergeSort(std::vector<int>* sampIn):
        SortObject(9,sampIn)
    {}

    // 二路归并排序函数声明
    void mergeSort(std::vector<int>& arr, int left, int right);
    // 辅助函数：合并两个已排序数组
    void merge(std::vector<int>& arr, int left, int mid, int right);

public slots:
    void sort() override;

};


//////////////
// 基数排序类,编号10
class RadixSort : public SortObject
{
    Q_OBJECT
public:
    explicit RadixSort(std::vector<int>* sampIn):
        SortObject(10,sampIn)
    {}

    // 基数排序函数声明
    void radixSort(std::vector<int>& arr);
    // 辅助函数：获取数组中的最大值
    int getMax(std::vector<int>& arr);
    // 辅助函数：对数组按照指定位数进行计数排序
    void countSort(std::vector<int>& arr, int exp);

public slots:
    void sort() override;

};



#endif // ALLSORT_H
