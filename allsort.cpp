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
    pause();
    if(interruptRequested)return;
    binaryInsertionSort(*sample);
    if(interruptRequested)return;
    emit completeSignal();
}

void HalfInsertSort::binaryInsertionSort(std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        int key = arr[i];
        int left = 0;
        int right = i - 1;
        if(interruptRequested)return;

        // 使用折半查找找到插入位置
        while (left <= right) {
            if(interruptRequested)return;
            int mid = left + (right - left) / 2;
            if (arr[mid] > key && comparing(mid,i)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        // 将插入位置右边的元素向右移动一位
        for (int j = i - 1; j >= left; --j) {
            if(interruptRequested)return;
            swapping(j, j+1);
        }
    }
}

///////////////
//希尔排序类,编号3
void ShellSort::sort()
{
    pause();
    if(interruptRequested)return;
    shellSort(*sample);
    if(interruptRequested)return;
    emit completeSignal();
}

void ShellSort::shellSort(std::vector<int>& arr) {
    size_t n = arr.size();
    // 初始化间隔 gap
    for (size_t gap = n / 2; gap > 0; gap /= 2) {
        if(interruptRequested)return;
        // 从 gap 位置开始，进行插入排序
        for (size_t i = gap; i < n; ++i) {
            if(interruptRequested)return;
            // 将 arr[i] 插入到已排好序的子序列中
            for (size_t j = i; j >= gap && arr[j] < arr[j - gap] && comparing(j,j-gap); j -= gap) {
                if(interruptRequested)return;
                swapping(j, j - gap);
            }
        }
    }
}


///////////////
//冒泡排序类,编号4
void BubbleSort::sort()
{
    pause();
    if(interruptRequested)return;
    optimizedBubbleSort(*sample);
    if(interruptRequested)return;
    emit completeSignal();
}

void BubbleSort::optimizedBubbleSort(std::vector<int>& arr) {
    size_t n = arr.size();
    bool swapped;
    for (size_t i = 0; i < n - 1; ++i) {
        if(interruptRequested)return;
        swapped = false;
        for (size_t j = 0; j < n - i - 1; ++j) {
            if(interruptRequested)return;
            if (arr[j] > arr[j + 1] && comparing(j,j+1)) {
                swapping(j,j+1);
                swapped = true;
            }
        }
        // 如果在内层循环中没有交换发生，说明数组已经有序，可以提前终止排序
        if (!swapped) {
            break;
        }
    }
}


///////////////
//快速排序类,编号5
void QuickSort::sort()
{
    pause();
    if(interruptRequested)return;
    quickSort(*sample,0,sample->size()-1);
    if(interruptRequested)return;
    emit completeSignal();
}

void QuickSort::quickSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        if(interruptRequested)return;
        int pivotIndex = partition(arr, left, right);
        quickSort(arr, left, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, right);
    }
}

int QuickSort::partition(std::vector<int>& arr, int left, int right) {
    int pivot = arr[right]; // 选择最右边的元素作为枢轴
    int i = left - 1; // i 是小于枢轴的元素的索引

    for (int j = left; j < right; ++j) {
        if(interruptRequested)return 0;
        if (arr[j] <= pivot && comparing(j,right)) {
            ++i;
            swapping(i,j);
        }
    }
    swapping(i+1,right); // 将枢轴放置到正确的位置
    return i + 1; // 返回枢轴的位置
}


//////////////
//直接选择排序类,编号6
void SimpleSelectSort::sort()
{
    pause();
    if(interruptRequested)return;
    selectionSort(*sample);
    if(interruptRequested)return;
    emit completeSignal();
}

void SimpleSelectSort::selectionSort(std::vector<int>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        // 假设最小元素的索引为i
        size_t minIndex = i;
        if(interruptRequested)return;
        // 寻找未排序部分的最小元素
        for (size_t j = i + 1; j < n; ++j) {
            if(interruptRequested)return;
            if (arr[j] < arr[minIndex] && comparing(j,minIndex)) {
                minIndex = j;
            }
        }
        // 将找到的最小元素和当前位置的元素交换
        if (minIndex != i) {
            swapping(i,minIndex);
        }
    }
}


//////////////
//堆排序类,编号7
void HeapSort::sort()
{
    pause();
    if(interruptRequested)return;
    heapSort(*sample);
    if(interruptRequested)return;
    emit completeSignal();
}

void HeapSort::heapSort(std::vector<int>& arr) {
    int n = arr.size();

    // 构建初始最大堆
    for (int i = n / 2 - 1; i >= 0; --i) {
        if(interruptRequested)return;
        heapify(arr, n, i);
    }

    // 逐个从堆中取出元素并进行堆调整
    for (int i = n - 1; i > 0; --i) {
        if(interruptRequested)return;
        swapping(0,i);
        heapify(arr, i, 0);
    }
}

void HeapSort::heapify(std::vector<int>& arr, int n, int i) {
    int largest = i; // 初始化最大值为根节点
    int left = 2 * i + 1; // 左子节点索引
    int right = 2 * i + 2; // 右子节点索引

    // 如果左子节点比根节点大
    if (left < n && arr[left] > arr[largest] && comparing(left,largest)) {
        largest = left;
    }

    // 如果右子节点比当前最大值大
    if (right < n && arr[right] > arr[largest] && comparing(right,largest)) {
        largest = right;
    }

    // 如果最大值不是根节点
    if (largest != i) {
        swapping(i,largest);

        // 递归地调整受影响的子树
        heapify(arr, n, largest);
    }
}


//////////////
//树形选择排序类,编号8
void TreeSelectSort::sort()
{
    pause();
    if(interruptRequested)return;
    tournamentSort(*sample);
    if(interruptRequested)return;
    emit completeSignal();
}

// 树形选择排序（锦标赛排序）函数
void TreeSelectSort::tournamentSort(std::vector<int>& arr) {
    int n = arr.size();
    int nodeSum = 2 * n - 1;
    std::vector<int> tree(nodeSum,0);


    ////////////////////////////////////////
    //给n个最初数据赋予值为0~n-1的顺序标识符值,使用以下辅助数组记录从"树的顺序存储索引"到"对应数据标识符值"的映射
    std::vector<int> treeIndexToIdentifierVal(nodeSum,-1);
    //记录"标识符值"到"当前数组arr内元素索引"的映射
    std::vector<int> identifierValToArrIndexNow(n,-1);
    //记录"当前数组arr内元素索引"到"标识符值"的映射
    std::vector<int> arrIndexNowToIdentifierVal(n,-1);
    ///////////////////////////////////////


    //录入叶子节点
    for(int i = n - 1,j = 0 ; i >= 0; i--, j++){
        tree[nodeSum - j - 1] = arr[i];
        treeIndexToIdentifierVal[nodeSum - j - 1] = i;
        identifierValToArrIndexNow[i] = i;
        arrIndexNowToIdentifierVal[i] = i;
    }
    //录入非叶子节点,构建初始树
    for(int i = nodeSum - n - 1;i >= 0; i--){
        if(interruptRequested)return;
        comparing(identifierValToArrIndexNow[treeIndexToIdentifierVal[2*i+1]],identifierValToArrIndexNow[treeIndexToIdentifierVal[2*i+2]]);
        if(tree[2*i+1]<tree[2*i+2]){
            tree[i] = tree[2*i+1];
            treeIndexToIdentifierVal[i] = treeIndexToIdentifierVal[2*i+1];
        }else{
            tree[i] = tree[2*i+2];
            treeIndexToIdentifierVal[i] = treeIndexToIdentifierVal[2*i+2];
        }
    }

    //每次找出最小元素并复制到原数组,一共循环n次,也即将所有元素全部排序
    int k = 0, minindex = -1;
    while(k < n - 1){
        if(interruptRequested)return;
        //当前的树根节点值即为最小元素
        //被交换元素具有的标识符值,以及交换前的"当前arr内索引"
        int identifier_1 = arrIndexNowToIdentifierVal[k];
        int identifier_2 = treeIndexToIdentifierVal[0];
        int arrIndex_1 = k;
        int arrIndex_2 = identifierValToArrIndexNow[identifier_2];

        //开始交换,并修改状态记录
        swapping(arrIndex_1,arrIndex_2);
        std::swap(identifierValToArrIndexNow[identifier_1],identifierValToArrIndexNow[identifier_2]);
        std::swap(arrIndexNowToIdentifierVal[arrIndex_1],arrIndexNowToIdentifierVal[arrIndex_2]);
        k++;
        minindex = treeIndexToIdentifierVal[0] + n - 1;
        tree[minindex] = INT_MAX;

        //若此节点有父节点，将其兄弟节点值提升到父节点位置
        while(minindex > 0){
            if(interruptRequested)return;
            if(minindex % 2 == 1){
                //该节点为左节点
                comparing(identifierValToArrIndexNow[treeIndexToIdentifierVal[minindex]],identifierValToArrIndexNow[treeIndexToIdentifierVal[minindex + 1]]);
                if(tree[minindex] < tree[minindex + 1]){
                    tree[(minindex - 1)/2] = tree[minindex];
                    treeIndexToIdentifierVal[(minindex - 1)/2] = treeIndexToIdentifierVal[minindex];
                }else{
                    tree[(minindex - 1)/2] = tree[minindex + 1];
                    treeIndexToIdentifierVal[(minindex - 1)/2] = treeIndexToIdentifierVal[minindex + 1];
                }
                minindex = (minindex - 1)/2;
            }else{
                //该节点为右节点
                comparing(identifierValToArrIndexNow[treeIndexToIdentifierVal[minindex]],identifierValToArrIndexNow[treeIndexToIdentifierVal[minindex - 1]]);
                if(tree[minindex] < tree[minindex - 1]){
                    tree[minindex/2 - 1] = tree[minindex];
                    treeIndexToIdentifierVal[minindex/2 - 1] = treeIndexToIdentifierVal[minindex];
                }else{
                    tree[minindex/2 - 1] = tree[minindex - 1];
                    treeIndexToIdentifierVal[minindex/2 - 1] = treeIndexToIdentifierVal[minindex - 1];
                }
                minindex = minindex/2 - 1;
            }
        }
    }
}


//////////////
//二路归并排序类,编号9
//////////////
void MergeSort::sort()
{
    pause();
    if(interruptRequested)return;
    mergeSort(*sample,0,sample->size()-1);
    if(interruptRequested)return;
    emit completeSignal();
}


void MergeSort::mergeSort(std::vector<int>& R,int s,int t) //被MergeSort2调用
{
    if (s>=t) return;			//R[s..t]的长度为0或者1时返回
    int m=(s+t)/2;			//取中间位置m
    mergeSort(R,s,m);		//对前子表排序
    mergeSort(R,m+1,t);		//对后子表排序
    merge(R,s,m,t);			//将两个有序子表合并成一个有序表
}


void MergeSort::merge(std::vector<int>& R,int low,int mid,int high)
//将R[low..mid]和R[mid+1..high]两个有序段归并为一个有序段R[low..high]
{
    std::vector<int> R1;
    R1.resize(high-low+1);	    //设置R1的长度为high-low+1
    int i=low,j=mid+1,k=0;	    //k是R1的下标,i、j分别为第1、2段的下标
    while (i<=mid && j<=high)	    //在第1段和第2段均未扫描完时循环
    {
        if (R[i]<=R[j] && comparing(i,j))		    //将第1段中的元素放入R1中
        {
            R1[k]=R[i];
            i++; k++;
        }
        else			    //将第2段中的元素放入R1中
        {
            R1[k]=R[j];
            j++; k++;
        }
    }
    while (i<=mid)		    //将第1段余下部分复制到R1
    {
        R1[k]=R[i];
        i++; k++;
    }
    while (j<=high)		    //将第2段余下部分复制到R1
    {
        R1[k]=R[j];
        j++; k++;
    }
    for (k=0,i=low;i<=high;k++,i++){
        //将R1复制回R中
        R[i]=R1[k];
        assigning(i);
    }
}


//////////////
// 基数排序类,编号10
//////////////
void RadixSort::sort()
{
    pause();
    if(interruptRequested)return;
    radixSort(*sample);
    if(interruptRequested)return;
    emit completeSignal();
}

// 基数排序函数定义
void RadixSort::radixSort(std::vector<int>& arr) {
    int maxNum = getMax(arr);

    // 对每一位进行计数排序
    for (int exp = 1; maxNum / exp > 0; exp *= 10) {
        countSort(arr, exp);
    }
}

// 获取数组中的最大值的辅助函数定义
int RadixSort::getMax(std::vector<int>& arr) {
    int maxNum = arr[0];
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i] > maxNum) {
            maxNum = arr[i];
        }
    }
    return maxNum;
}

// 对数组按照指定位数进行计数排序的辅助函数定义
void RadixSort::countSort(std::vector<int>& arr, int exp) {
    int n = arr.size();
    std::vector<int> output(n);
    int count[10] = {0};

    // 计算每个数字出现的次数
    for (int i = 0; i < n; ++i) {
        count[(arr[i] / exp) % 10]++;
    }

    // 将 count[i] 转换为当前数字的位置
    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }

    // 构造排序后的数组
    for (int i = n - 1; i >= 0; --i) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // 将排序后的数组复制回原数组
    for (int i = 0; i < n; ++i) {
        arr[i] = output[i];
        assigning(i);
    }
}



