#include "mysort.h"
#include<QDebug>
Mysort::Mysort(QObject *parent)
    : QObject{parent}
{}
void Mysort::work(std::vector<int>sort_numbers,int i,int speed)
{
    if(sorted)
    {
        return ;
    }
    qDebug()<<i;
    switch(i)
    {
    case 0:
        bubble(sort_numbers, speed);
        break;
    case 1:
        select(sort_numbers, speed);
        break;
    case 2:
        inserySort(sort_numbers,speed);
        break;
    case 3:
        shellSort(sort_numbers,speed);
        break;
    case 5:
        mergeSort(sort_numbers,speed);
        break;
    case 4:
        radixSort(sort_numbers,speed);
        break;
    case 6:
        quickSort(sort_numbers,speed);
        break;
    case 7:
        heapSort(sort_numbers,speed);
        break;
    }
    sorted=1;
    emit send_end();
}
void Mysort::bubble(std::vector<int>&arr,int speed){
    int size=arr.size();
    int swaptime=0;
    int cmptime=0;

    for(int i=0;i<size-1;i++)
    {
        bool swapOrNot=0;
        for(int j=0;j<size-i-1;j++)
        {
            emit change_color_swap(j,j+1,true);
            emit sent_cmp(++cmptime);
            QThread::msleep(speed);
            if(arr[j]>arr[j+1])
            {
                swapOrNot=1;
                QThread::msleep(speed);
                emit swap_columns(j,j+1,arr);
                emit sent_swap(++swaptime);
                swap(j,j+1,arr);
            }
            emit change_color_swap(j,j+1,false);
        }
        emit sent_cmp(++cmptime);
        if(swapOrNot==0)
        {
            break;
        }
    }
}
void Mysort::select(std::vector<int> &arr,int speed)
{
    int swaptime=0;
    int cmptime=0;
    int size=arr.size();
    for (int i = 0; i < size-1; i++) {
        // 寻找[i, n-1]区间里的最小值的索引
        int min_idx = i;
        for (int j = i+1; j < size; j++)
        {
            emit change_color_swap(j,min_idx,true);
            QThread::msleep(speed);
            emit change_color_swap(j,min_idx,false);
            emit sent_cmp(++cmptime);
            if (arr[j] < arr[min_idx])
                min_idx = j;

        }

        // 交换找到的最小值到它应该在的位置
        if(i!=min_idx){
            QThread::msleep(speed);
            emit swap_columns(min_idx,i,arr);
            emit sent_swap(++swaptime);
            swap(min_idx, i,arr);}
    }
}
void Mysort::inserySort(std::vector<int>&arr,int speed){
    int temp=0;
    int swaptime=0;
    int cmptime=0;
    int len=arr.size();
    int j=0;
    for ( int i = 1; i < len; i++) {
        emit sent_cmp(++cmptime);
        emit change_color_swap(i,i-1,true);
        QThread::msleep(speed);
        emit change_color_swap(i,i-1,false);
        //若a[i]关键字小于前驱
        if (arr[i] < arr[i - 1]) {
            //temp 暂存a[i]
            temp = arr[i];
            //检查前面所有已经排好序的元素
            for (j = i - 1; j >= 0 && arr[j] > temp; j--) {
                //所有大于temp的元素都后移
                emit sent_cmp(++cmptime);
                emit change_color_swap(j,i,true);
                QThread::msleep(speed);
                emit change_color_swap(j,i,false);

                emit sent_update(++update_time);
                emit change_columns(j+1,arr[j],true);
                QThread::msleep(speed/3);
                emit change_columns(j+1,arr[j],false);
                arr[j + 1] = arr[j];
            }
            //复制到插入位置
            emit sent_update(++update_time);
            emit change_columns(j+1,temp,true);
            QThread::msleep(speed/3);
            emit change_columns(j+1,temp,false);
            arr[j + 1] = temp;
        }
    }
}
void Mysort::shellSort(std::vector<int>&arr,int speed){
    int cmptime=0,swaptime=0;
    int len=arr.size();
    int gap=len/2;
    while(gap>=1)
    {
        for (int i = gap; i < len; ++i) //i值每次改变可以处理到不同的子序列
        {
            emit sent_cmp(++cmptime);
            emit change_color_swap(i,i-gap,true);
            QThread::msleep(speed);
            emit change_color_swap(i-gap,i,false);
            if (arr[i] < arr[i - gap])
            {
                int temp = arr[i]; ;//暂存arr[i]值，防止后续移动元素时值被覆盖
                int j;
                for (j = i - gap; j >= 0 && arr[j] > temp; j -= gap) //检查所有前面排好序的元素
                {
                    emit sent_cmp(++cmptime);
                    emit change_color_swap(i,j,true);
                    QThread::msleep(speed);
                    emit change_color_swap(j,i,false);


                     emit sent_update(++update_time);
                    emit change_columns(j+gap,arr[j],true);
                    QThread::msleep(speed/3);
                    emit change_columns(j+gap,arr[j],false);
                    arr[j + gap] = arr[j]; //所有大于temp的元素都向后移动
                }
                 emit sent_update(++update_time);
                emit change_columns(j+gap,temp,true);
                QThread::msleep(speed/3);
                emit change_columns(j+gap,temp,false);
                arr[j + gap] = temp; //复制数据到插入位置，注意j因为被减了gap，这里加回来
            }
        }
        gap/=2;
    }
}
void Mysort::mergeSort(std::vector<int>&arr,int speed){
    int cmptime=0,swaptime=0;
    int gap = 1,n = arr.size();
    std::vector<int> tmp(n);//辅助数组
    while(gap < n) //gap为几：几个几个元素之间归并
    {
        //推导范围:因为gap个元素作为一个区间，两个区间进行归并,所以下一轮：i+=2*gap
        //[i,i+gap-1] [i+gap,i + 2* gap - 1]
        for(int i = 0;i<n;i += 2*gap)
        {
            int begin1 = i,end1 = i+gap-1;
            int begin2 = i + gap,end2 = i+2*gap-1;
            //由于是归并一部分，然后拷贝一部分回去,所以如果某一个区间越界了,那么本轮就不需要归并了
            emit sent_cmp(++cmptime);
            QThread::msleep(speed/3);
            if(begin1 >=n || begin2 >= n) break;

            emit sent_cmp(++cmptime);
            QThread::msleep(speed/3);
            if(end2 >= n) end2 = n-1;//修正结束位置

            //[begin1,end1] [begin2,end2]
            int index = i;//归并元素从tmp的哪个位置开始向后拷贝

            emit sent_cmp(++cmptime);
            QThread::msleep(speed/3);
            while(begin1 <= end1 && begin2 <= end2)
            {

                if(arr[begin1] > arr[begin2])
                {
                    emit sent_update(++update_time);
                    QThread::msleep(speed/3);
                    tmp[index++] = arr[begin2++];
                }
                else
                {
                   emit sent_update(++update_time);
                    QThread::msleep(speed/3);
                    tmp[index++] = arr[begin1++];
                }
            }
            while(begin1 <= end1) {
                tmp[index++] = arr[begin1++];
                emit sent_update(++update_time);
                QThread::msleep(speed/3);
            }
            while(begin2 <= end2) {
                tmp[index++] = arr[begin2++];
                emit sent_update(++update_time);
                QThread::msleep(speed/3);
            }

            //拷贝回去原数组 区间为:[i(begin1),end2]
            //由于begin1已经改变,所以要使用i变量
            for(int j = i;j<=end2;j++)
            {
                emit change_columns(j,tmp[j],true);
                arr[j] = tmp[j];
                 emit sent_update(++update_time);
                QThread::msleep(speed/3);
                emit change_columns(j,tmp[j],false);
            }
        }
        gap *= 2;
    }

}
//基数排序
void Mysort::radixSort(std::vector<int> &arr, int speed)
{
    int cmptime=0;
    int swaptime=0;
    int n=arr.size();
    int maxIndex =0 ;
    for (int i = 1; i < n; i++) {
        emit sent_cmp(++cmptime);
        emit change_color_swap(i,maxIndex,true);
        QThread::msleep(speed);
        emit change_color_swap(i,maxIndex,false);
        if (arr[i] > arr[maxIndex]) {
            maxIndex=i;
        }
    }
    int temp=arr[maxIndex];
    for (int exp = 1; temp / exp > 0; exp *= 10) {
        countingSort(arr, exp,speed,cmptime,swaptime);
    }


}
void Mysort::countingSort(std::vector<int>&arr,int exp,int speed,int &cmptime,int &swaptime){
    const int RADIX = 10;
    std::vector<int> output(arr.size());
    std::vector<int> count(RADIX, 0);

    // 统计每个桶中的元素个数
    for (int i = 0; i < arr.size(); i++) {
         emit sent_update(++update_time);
        QThread::msleep(speed/3);
        count[(arr[i] / exp) % RADIX]++;
    }

    // 计算每个桶的累积个数
    for (int i = 1; i < RADIX; i++) {
        emit sent_update(++update_time);
        QThread::msleep(speed/3);
        count[i] += count[i - 1];
    }

    // 根据累积个数将元素放入输出数组中
    for (int i = arr.size() - 1; i >= 0; i--) {
        emit sent_update(++update_time);
        QThread::msleep(speed/3);
        output[count[(arr[i] / exp) % RADIX] - 1] = arr[i];
         emit sent_update(++update_time);
        QThread::msleep(speed/3);
        count[(arr[i] / exp) % RADIX]--;
    }

    // 将输出数组复制回原始数组
    for (int i = 0; i < arr.size(); i++) {
         emit sent_update(++update_time);
        emit change_columns(i,output[i],true);
        QThread::msleep(speed/3);
        emit change_columns(i,output[i],false);
        arr[i] = output[i];
    }
}
void Mysort::quickSort(std::vector<int>&arr,int speed){

    int cmptime=0, swaptime=0;

    std::stack<int> st;
    //初始时，将整个数组的边界入栈
    st.push(0);
    st.push(arr.size() - 1);
    //迭代地从栈中取出边界，对相应的子数组执行划分操作
    while (!st.empty())
    {
        int right = st.top();
        st.pop();
        int left = st.top();
        st.pop();
        int keyi = partSort(arr, left, right,speed,cmptime,swaptime);
        //将划分后的两个子数组的边界入栈
        if (keyi + 1 < right)
        {
            emit sent_cmp(++cmptime);
            //QThread::msleep(speed/3);
            st.push(keyi + 1);
            st.push(right);
        }
        if (keyi - 1 > left)
        {
            emit sent_cmp(++cmptime);
            //QThread::msleep(speed/3);
            st.push(left);
            st.push(keyi - 1);
        }
    }
}
int Mysort::partSort(std::vector<int>&arr,int begin,int end,int speed,int &cmptime,int&swaptime){
    int left = begin, right = end;
    int keyi = begin;
    while (left < right)
    {
        emit sent_cmp(++cmptime);
        QThread::msleep(speed/3);
        //右边找小
        while (left < right && arr[right] >= arr[keyi])
        {
            emit sent_cmp(++cmptime);
            emit sent_cmp(++cmptime);
            emit change_color_swap(right,keyi,true);
            QThread::msleep(speed/3);
            emit change_color_swap(right,keyi,false);

            right--;
        }

        //左边找大
        while (left < right && arr[left] < arr[keyi])
        {
            emit sent_cmp(++cmptime);
            emit sent_cmp(++cmptime);
            emit change_color_swap(left,keyi,true);
            QThread::msleep(speed/3);
            emit change_color_swap(left,keyi,false);

            left++;
        }
        emit sent_swap(++swaptime);
        QThread::msleep(speed);
        emit swap_columns(left,right,arr);
        swap(left, right,arr);
    }
    emit sent_swap(++swaptime);
    QThread::msleep(speed);
    emit swap_columns(left,keyi,arr);
    swap(left, keyi,arr);
    return left;

}
// 堆排序函数
void Mysort::heapSort(std::vector<int>& arr,int speed) {
    int cmptime=0,swaptime=0;
    int len = arr.size();
    int i = len / 2 - 1;
    while (i >= 0) { // 遍历每一个父节点以构造最大堆
        heapify(arr, i, len - 1,cmptime,swaptime,speed);
        i--;
    }
    for (int i = len - 1; i >= 0; i--) { // 利用最大堆开始排序
        emit swap_columns(i,0,arr);
        emit sent_swap(++swaptime);
        QThread::msleep(speed);
        swap(i, 0,arr);
        heapify(arr, 0, i - 1,cmptime,swaptime,speed); // 调整新的堆使其成为最大堆
    }

}
void Mysort:: heapify(std::vector<int>& arr, int start, int end,int& cmptime,int& swaptime,int& speed) {

    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) { // 保证节点在有效范围内
        if ((son < end) && arr[son] < arr[son + 1]) { //有右节点同时右节点比左节点大
            son++;  // 让i指向子节点里最大的
            emit sent_cmp(++cmptime);
            emit change_color_swap(son,son+1,true);
            QThread::msleep(speed);
            emit change_color_swap(son,son+1,false);
        }
        if (arr[dad] > arr[son]) {
            emit sent_cmp(++cmptime);
            emit change_color_swap(son,dad,true);
            QThread::msleep(speed);
            emit change_color_swap(son,dad,false);
            // 这是一个需要好好理解的break：我们从最后一个非叶子节点自底向上开始迭代的，
            // 也就是说在当前父节点下的子树是已经成为了最大堆的，所以当此处的父节点值大于其两个子节点时是可以直接break的
            break;
        } else {
            emit sent_swap(++swaptime);
            emit swap_columns(dad,son,arr);
            QThread::msleep(speed);
            swap(dad, son,arr);
            // 更新根节点和左子节点
            dad = son;
            son = 2 * dad + 1;
        }
    }
}
void Mysort::swap(int i,int j,std::vector<int>&arr)
{
    int temp=arr[i];
    arr[i]=arr[j];
    arr[j]=temp;
}
