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

        // 使用折半查找找到插入位置
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] > key && comparing(mid,i)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        // 将插入位置右边的元素向右移动一位
        for (int j = i - 1; j >= left; --j) {
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
        // 从 gap 位置开始，进行插入排序
        for (size_t i = gap; i < n; ++i) {
            // 将 arr[i] 插入到已排好序的子序列中
            for (size_t j = i; j >= gap && arr[j] < arr[j - gap] && comparing(j,j-gap); j -= gap) {
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
        swapped = false;
        for (size_t j = 0; j < n - i - 1; ++j) {
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
        int pivotIndex = partition(arr, left, right);
        quickSort(arr, left, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, right);
    }
}

int QuickSort::partition(std::vector<int>& arr, int left, int right) {
    int pivot = arr[right]; // 选择最右边的元素作为枢轴
    int i = left - 1; // i 是小于枢轴的元素的索引

    for (int j = left; j < right; ++j) {
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
        // 寻找未排序部分的最小元素
        for (size_t j = i + 1; j < n; ++j) {
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
        heapify(arr, n, i);
    }

    // 逐个从堆中取出元素并进行堆调整
    for (int i = n - 1; i > 0; --i) {
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

    // 生成一个2*n大小的完全二叉树
    std::vector<int> tree(2 * n, 0);

    // 将数据放到树的叶子节点上,即索引闭区间[n,2n-1].原位置索引i对应此区间内索引n+i
    for (int i = 0; i < n; ++i) {
        tree[n + i] = arr[i];
    }

    //映射表.索引为"元素在经过一部分交换操作后在部分有序数组内的索引值",而映射值为"元素在初始无序数组内部的索引值"
    //即从现状到初态
    //在每一个时刻,mapper[k]表明了当前状态下数组中的元素顺序索引
    //而k等于上述arr[mapper[k]]当前状态元素,其最初状态下的元素索引
    std::vector<int> mapper;
    for(int i = 0; i < n; ++i){
        mapper.push_back(i);
    }
    //初始化.
    //反向映射器.即从初态到现状
    std::vector<int> inverseMapper = mapper;
    //结点映射器.从当前的结点索引映射到对应元素的现状索引
    std::vector<int> linkMapper(2 * n,0);
    for(int i=n;i<2 * n;i++){
        linkMapper[i]=i-n;
    }

    // 构建树，从叶子节点往上构建.tree[0]没有意义.
    for (int i = n - 1; i > 0; --i) {
        if(tree[2 * i]<tree[2 * i + 1]){
            tree[i]=tree[2 * i];
            linkMapper[i]=linkMapper[2 * i];
        }else{
            tree[i]=tree[2 * i + 1];
            linkMapper[i]=linkMapper[2 * i + 1];
        }
        comparing(linkMapper[2 * i],linkMapper[2 * i + 1]);
    }

    // 逐个找到最小元素并替换.此处的每个循环单元中,发生的交换均需要对应依次mapper的更新
    for (int i = 0; i < n; ++i) {
        // i表示"需要让位元素的当前索引"
        // 根节点就是最小元素.此行为相当于交换了当前状态下的arr[i]和arr[mapper[pos-n]],使得mapper[pos-n]变为mapper[i],而mapper[i]变为mapper[pos-n]
        // 当前索引为i,原本索引为x(未知)的元素当前索引变为
        arr[i] = tree[1];
        // 交换的目标A:索引由i指定.
        // 交换的目标B:索引由当前的最小元素决定.tree内只记录了该最小元素最初状态下的索引值pos-n.因此引入mapper记忆器

        // 找到这个最小元素在树中的位置,查找范围为索引闭区间[n,2n-1]
        int pos = std::distance(tree.begin(), std::find(tree.begin() + n, tree.end(), tree[1]));
        swapping(i,inverseMapper[pos-n]);
        std::swap(mapper[i],mapper[pos-n]);
        std::swap(inverseMapper[mapper[i]],inverseMapper[mapper[pos-n]]);
        std::swap(linkMapper[mapper[i]+n],linkMapper[mapper[pos-n]+n]);



        // 用一个大的值替换掉最小元素
        tree[pos] = INT_MAX;

        // 重新构建树
        for (int j = pos / 2; j > 0; j /= 2) {
            if(tree[2 * j]<tree[2 * j + 1]){
                tree[j]=tree[2 * j];
                linkMapper[j]=linkMapper[2 * j];
            }else{
                tree[j]=tree[2 * j + 1];
                linkMapper[j]=linkMapper[2 * j + 1];
            }
            comparing(linkMapper[2 * j],linkMapper[2 * j + 1]);
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

// 二路归并排序函数定义
void MergeSort::mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// 合并两个已排序数组的辅助函数定义
void MergeSort::merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // 创建临时数组来存储左右两个子数组
    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);

    // 将数据复制到临时数组中
    for (int i = 0; i < n1; ++i) {
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        rightArr[j] = arr[mid + 1 + j];
    }

    // 合并临时数组并将结果存回原数组
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    // 将剩余的元素复制回原数组
    while (i < n1) {
        arr[k++] = leftArr[i++];
    }
    while (j < n2) {
        arr[k++] = rightArr[j++];
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
    }
}



