#include "allsort.h"

///////////////
//直接插入排序类,编号1
void SimpleInsertSort::sort()
{
    pause();
    if(interruptRequested)return;
    InsertSort(*sample,sample->size());
    if(interruptRequested)return;
    emit completeSignal();
}

void SimpleInsertSort::InsertSort(std::vector<int>& R,int n) 	//直接插入排序
{
    for (int i = 1; i < n; ++i) {
        if(interruptRequested)return;
        int j = i;
        while (j > 0 && comparing(j,j-1) && R[j] < R[j - 1]) {
            swapping(j,j-1);
            //std::swap(R[j], R[j - 1]);
            --j;
        }
    }
}

///////////////
//折半插入排序类,编号2
void HalfInsertSort::sort()
{

}


///////////////
//希尔排序类,编号3
void ShellSort::sort()
{

}


///////////////
//冒泡排序类,编号4
void BubbleSort::sort()
{

}


///////////////
//快速排序类,编号5
void QuickSort::sort()
{

}


//////////////
//直接选择排序类,编号6
void SimpleSelectSort::sort()
{

}


//////////////
//堆排序类,编号7
void HeapSort::sort()
{

}


//////////////
//树形选择排序类,编号8
void TreeSelectSort::sort()
{

}



//////////////
//二路归并排序类,编号9
void MergeSort::sort()
{

}



//////////////
// 基数排序类,编号10
void RadixSort::sort()
{

}


