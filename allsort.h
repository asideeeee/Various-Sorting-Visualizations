#ifndef ALLSORT_H
#define ALLSORT_H

#include "sortobject.h"
#include "basecanva.h"

///////////////
//直接选择排序类,编号1
class SimpleInsertSort : public SortObject
{
    Q_OBJECT
public:
    explicit SimpleInsertSort(QObject *parent = nullptr):
        SortObject(parent)
        ,parentCanva(dynamic_cast<BaseCanva*>(parent))
    {}

    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

    //该类的parentCanva成员即画布.请通过parent访问所需要的数据
signals:
private:
    BaseCanva* parentCanva;
};


///////////////
//折半插入排序类,编号2
class HalfInsertSort : public SortObject
{
    Q_OBJECT
public:
    explicit HalfInsertSort(QObject *parent = nullptr):
        SortObject(parent)
        ,parentCanva(dynamic_cast<BaseCanva*>(parent))
    {}

    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

signals:
private:
    BaseCanva* parentCanva;
};


///////////////
//希尔排序类,编号3
class ShellSort : public SortObject
{
    Q_OBJECT
public:
    explicit ShellSort(QObject *parent = nullptr):
        SortObject(parent)
        ,parentCanva(dynamic_cast<BaseCanva*>(parent))
    {}

    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

signals:
private:
    BaseCanva* parentCanva;
};


///////////////
//冒泡排序类,编号4
class BubbleSort : public SortObject
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr):
        SortObject(parent)
        ,parentCanva(dynamic_cast<BaseCanva*>(parent))
    {}

    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

signals:
private:
    BaseCanva* parentCanva;
};


///////////////
//快速排序类,编号5
class QuickSort : public SortObject
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr):
        SortObject(parent)
        ,parentCanva(dynamic_cast<BaseCanva*>(parent))
    {}

    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

signals:
private:
    BaseCanva* parentCanva;
};


//////////////
//直接选择排序类,编号6
class SimpleSelectSort : public SortObject
{
    Q_OBJECT
public:
    explicit SimpleSelectSort(QObject *parent = nullptr):
        SortObject(parent)
        ,parentCanva(dynamic_cast<BaseCanva*>(parent))
    {}

    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

signals:
private:
    BaseCanva* parentCanva;
};

//////////////
//堆排序类,编号7
class HeapSort : public SortObject
{
    Q_OBJECT
public:
    explicit HeapSort(QObject *parent = nullptr):
        SortObject(parent)
        ,parentCanva(dynamic_cast<BaseCanva*>(parent))
    {}

    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

signals:
private:
    BaseCanva* parentCanva;
};

//////////////
//树形选择排序类,编号8
class TreeSelectSort : public SortObject
{
    Q_OBJECT
public:
    explicit TreeSelectSort(QObject *parent = nullptr):
        SortObject(parent)
        ,parentCanva(dynamic_cast<BaseCanva*>(parent))
    {}

    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

signals:
private:
    BaseCanva* parentCanva;
};


//////////////
//二路归并排序类,编号9
class MergeSort : public SortObject
{
    Q_OBJECT
public:
    explicit MergeSort(QObject *parent = nullptr):
        SortObject(parent)
        ,parentCanva(dynamic_cast<BaseCanva*>(parent))
    {}

    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

signals:
private:
    BaseCanva* parentCanva;
};


//////////////
// 基数排序类,编号10
class RadixSort : public SortObject
{
    Q_OBJECT
public:
    explicit RadixSort(QObject *parent = nullptr):
        SortObject(parent)
        ,parentCanva(dynamic_cast<BaseCanva*>(parent))
    {}

    void sort(int count,int interval) override;
    void pause() override;
    void draw(QPainter* painter,int width,int height) override;

signals:
private:
    BaseCanva* parentCanva;
};

#endif // ALLSORT_H
