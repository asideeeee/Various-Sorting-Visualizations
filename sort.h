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
};
