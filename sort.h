#include <vector>
using namespace std;

class Sort {
private:
    vector<int> data;

public:
    void insertData(vector<int>& input);
    //数组的写入

    void clearData();
    //数组的清除

    void bubbleSort(vector<int> arr);
    //冒泡排序
};
