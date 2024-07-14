#ifndef ALLSORT_H
#define ALLSORT_H

#include "basecanva.h"

///////////////
//直接选择排序类,编号1
class SimpleInsertSort : public SortObject
{
    Q_OBJECT
public:
    explicit SimpleInsertSort(BaseCanva* canva,QObject *parent = nullptr):
        SortObject(1,canva)
    {}

    void sort() override;

};


///////////////
//折半插入排序类,编号2
class HalfInsertSort : public SortObject
{
    Q_OBJECT
public:
    explicit HalfInsertSort(BaseCanva* canva,QObject *parent = nullptr):
        SortObject(2,canva)
    {}

    void sort() override;

};


///////////////
//希尔排序类,编号3
class ShellSort : public SortObject
{
    Q_OBJECT
public:
    explicit ShellSort(BaseCanva* canva,QObject *parent = nullptr):
        SortObject(3,canva)
    {}

    void sort() override;

};


///////////////
//冒泡排序类,编号4
class BubbleSort : public SortObject
{
    Q_OBJECT
public:
    explicit BubbleSort(BaseCanva* canva,QObject *parent = nullptr):
        SortObject(4,canva)
    {}

    void sort() override;

};


///////////////
//快速排序类,编号5
class QuickSort : public SortObject
{
    Q_OBJECT
public:
    explicit QuickSort(BaseCanva* canva,QObject *parent = nullptr):
        SortObject(5,canva)
    {}

    void sort() override;

};


//////////////
//直接选择排序类,编号6
class SimpleSelectSort : public SortObject
{
    Q_OBJECT
public:
    explicit SimpleSelectSort(BaseCanva* canva,QObject *parent = nullptr):
        SortObject(6,canva)
    {}

    void sort() override;

};

//////////////
//堆排序类,编号7
class HeapSort : public SortObject
{
    Q_OBJECT
public:
    explicit HeapSort(BaseCanva* canva,QObject *parent = nullptr):
        SortObject(7,canva)
    {}

    void sort() override;

};

//////////////
//树形选择排序类,编号8
class TreeSelectSort : public SortObject
{
    Q_OBJECT
public:
    explicit TreeSelectSort(BaseCanva* canva,QObject *parent = nullptr):
        SortObject(8,canva)
    {}

    void sort() override;

};


//////////////
//二路归并排序类,编号9
class MergeSort : public SortObject
{
    Q_OBJECT
public:
    explicit MergeSort(BaseCanva* canva,QObject *parent = nullptr):
        SortObject(9,canva)
    {}

    void sort() override;

};


//////////////
// 基数排序类,编号10
class RadixSort : public SortObject
{
    Q_OBJECT
public:
    explicit RadixSort(BaseCanva* canva,QObject *parent = nullptr):
        SortObject(10,canva)
    {}

    void sort() override;

};

#endif // ALLSORT_H
