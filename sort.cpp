#include"sort.h"

//数组写入
void Sort::insertData(vector<int>& input) {
    data = input;
}

//数组清除
void Sort::clearData() {
    data.clear();
}

//冒泡排序
void Sort::bubbleSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 交换 arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}