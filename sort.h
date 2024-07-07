#include <vector>
#include<iostream>
using namespace std;
class Sort {
private:
    vector<int> data;

public:
    void insertData(const vector<int>& input);
    //插入数据

    void clearData();
    //清除数据

    void bubbleSort(vector<int>arr);
    //冒泡排序

    void heapSort(vector<int>arr,int n);
    //堆排序
    void siftDown(vector<int>& arr,int low,int high);
    //堆排序的辅助函数,自顶向下筛选

    void selectSort(vector<int> arr);
    //直接选择排序

    void treeSelectSort(vector<int> arr);
    //树形选择排序
    void minHeapify(vector<int>& arr, int n, int root);
    //树形选择排序辅助函数

    void mergeSort(vector<int> arr, int s, int t);
    //二路归并排序
    void Merge(vector<int>& arr, int low, int mid, int high);

    void radixSort(vector<int> arr);
    //基数排序函数
    void countingSort(vector<int>& arr, int exp);
    //基数排序的辅助函数1
    int getMax(const vector<int>& arr);
    //基数排序的辅助函数2
};
