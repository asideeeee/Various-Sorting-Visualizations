#ifndef ALLSORT_H
#define ALLSORT_H

#include "sortobject.h"


///////////////
//直接选择排序类,编号1
class SimpleInsertSort : public SortObject
{
    Q_OBJECT
public:
    explicit SimpleInsertSort(QObject *parent = nullptr):
        SortObject(parent){}

    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

signals:
};


///////////////
//折半插入排序类,编号2
class HalfInsertSort : public SortObject
{
    Q_OBJECT
public:
    explicit HalfInsertSort(QObject *parent = nullptr):
        SortObject(parent){}

    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

signals:
};


///////////////
//希尔排序类,编号3
class ShellSort : public SortObject
{
    Q_OBJECT
public:
    explicit ShellSort(QObject *parent = nullptr):
        SortObject(parent){}

    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

signals:
};


///////////////
//冒泡排序类,编号4
class BubbleSort : public SortObject
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr):
        SortObject(parent){}

    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

signals:
};


///////////////
//快速排序类,编号5
class QuickSort : public SortObject
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr):
        SortObject(parent){}
    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

signals:
};


//////////////
//直接选择排序类,编号6
class SimpleSelectSort : public SortObject
{
    Q_OBJECT
public:
    explicit SimpleSelectSort(QObject *parent = nullptr):
        SortObject(parent){}

    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

signals:
};

//////////////
//堆排序类,编号7
class HeapSort : public SortObject
{
    Q_OBJECT
public:
    explicit HeapSort(QObject *parent = nullptr):
        SortObject(parent){}

    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

signals:
};

//////////////
//树形选择排序类,编号8
class TreeSelectSort : public SortObject
{
    Q_OBJECT
public:
    explicit TreeSelectSort(QObject *parent = nullptr):
        SortObject(parent){}

    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

signals:
};


//////////////
//二路归并排序类,编号9
class MergeSort : public SortObject
{
    Q_OBJECT
public:
    explicit MergeSort(QObject *parent = nullptr):
        SortObject(parent){}

    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

signals:
};


//////////////
// 基数排序类,编号10
class RadixSort : public SortObject
{
    Q_OBJECT
public:
    explicit RadixSort(QObject *parent = nullptr):
        SortObject(parent){}

    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

signals:
};

#endif // ALLSORT_H
