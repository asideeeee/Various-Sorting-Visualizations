#include <vector>
using namespace std;

class Sort {
private:
    vector<int> data;

public:
    void insertData(vector<int>& input);
    //�����д��

    void clearData();
    //��������

    void bubbleSort(vector<int> arr);
    //ð������
};
