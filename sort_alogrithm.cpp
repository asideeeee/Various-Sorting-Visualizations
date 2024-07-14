#include "sort_alogrithm.h"

sort_Alogrithm::sort_Alogrithm(QObject *parent)
    : QThread{parent}
{

}
void sort_Alogrithm:: recInformation(int index,int speed,QVector<int>arr){
    Alogrithm_index=index;
    sort_numbers=arr;
    c_speed=speed;

}
void sort_Alogrithm::run()
{
    cmp=0;
    swp=0;
    switch(Alogrithm_index)
    {
    case 0:
        bubble();
        break;
    case 1:
        select();
        break;
    }
}
void sort_Alogrithm::bubble()
{

    for(int i=0;i<sort_numbers.size()-1;i++)
    {
        //QThread::usleep(c_speed);
        for(int j=0;j<sort_numbers.size()-1-i;j++)
        {           
            //sleep中参数可以改为speed；
            QThread::usleep(c_speed);
            if(sort_numbers[j]>sort_numbers[j+1])
            {

                emit Al_swap_columns(j,j+1,sort_numbers);
                emit send_swap(++swp);
                QThread::usleep(c_speed);
                swap(j,j+1);
            }
            emit send_cmp(++cmp);
        }
    }
}
void sort_Alogrithm:: select(){
    int n = sort_numbers.size();
    for (int i = 0; i < n - 1; i++) {
        // 假设当前位置i是最小值的位置
        int minIndex = i;
        // 在i之后（不包括i）的未排序序列中找到最小值的索引
        for (int j = i + 1; j < n; j++) {
            QThread::usleep(c_speed);
            if (sort_numbers[j] < sort_numbers[minIndex]) {
                minIndex = j;
                QThread::usleep(c_speed);
            }
            emit send_cmp(++cmp);
        }

        // 如果最小值不是当前位置i，则将其与i位置的元素交换
        if (minIndex != i) {
            QThread::usleep(c_speed);
            emit send_swap(++swp);
            emit Al_swap_columns(i,minIndex,sort_numbers);
            swap(i, minIndex);
        }
        emit send_cmp(++cmp);
    }
}
void sort_Alogrithm:: swap(int i,int j)
{
    int temp=sort_numbers[i];
    sort_numbers[i]=sort_numbers[j];
    sort_numbers[j]=temp;
}

