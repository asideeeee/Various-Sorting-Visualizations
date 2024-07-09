#include"sort.h"

//插入的实现
void Sort::insertData(const vector<int>& input) {
    data = input;
}

//清除的实现
void Sort::clearData() {
    data.clear();
}

//冒泡排序的实现
void Sort::bubbleSort(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

//堆排序辅助函数
void Sort::siftDown(vector<int>& arr,int low,int high){
   int i=low;
   int j=2*i+1;
   int tmp=arr[i];
   while (j<=high)
   {  if (j<high && arr[j]<arr[j+1])
         j++;
      if (tmp<arr[j]){
         arr[i]=arr[j];
         i=j;
         j=2*i+1;
      }
      else break;
   }
   arr[i]=tmp;
}

//堆排序实现.n是被传入数组arr的大小,调用时输入arr.size()即可
void Sort::heapSort(vector<int> arr,int n){
   for (int i=n/2-1;i>=0;i--)
      siftDown(arr,i,n-1);
   for (int i=n-1;i>0;i--)
   {  swap(arr[0],arr[i]);
      siftDown(arr,0,i-1);
   }
}

//直接选择排序实现
void Sort::selectSort(vector<int> arr)	{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)	
    {
        int minj = i;
        for (int j = i + 1; j < n; j++)	
            if (arr[j] < arr[minj])
                minj = j;	
        if (minj != i)	
            swap(arr[i], arr[minj]);
    }
}

//树形选择排序实现
void Sort::treeSelectSort(vector<int> arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; --i) {
        minHeapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        
        minHeapify(arr, i, 0);
    }
}

//树形选择排序的辅助函数(最小堆调整函数)
void Sort::minHeapify(vector<int>& arr, int n, int root) {
    int smallest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < n && arr[left] < arr[smallest]) {
        smallest = left;
    }

    if (right < n && arr[right] < arr[smallest]) {
        smallest = right;
    }

    if (smallest != root) {
        std::swap(arr[root], arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

//二路归并排序,调用时请使s=0,t=arr.size()
void Sort::mergeSort(vector<int> arr, int s, int t) 
{
    if (s >= t) return;		
    int m = (s + t) / 2;			
    mergeSort(arr, s, m);		
    mergeSort(arr, m + 1, t);		
    Merge(arr, s, m, t);			
}

//二路归并排序辅助函数
void Sort::Merge(vector<int>& arr, int low, int mid, int high){
    vector<int> arr1;
    arr1.resize(high - low + 1);	    
    int i = low, j = mid + 1, k = 0;	    
    while (i <= mid && j <= high)	    
    {
        if (arr[i] <= arr[j])		  
        {
            arr1[k] = arr[i];
            i++; k++;
        }
        else			
        {
            arr1[k] = arr[j];
            j++; k++;
        }
    }
    while (i <= mid)		
    {
        arr1[k] = arr[i];
        i++; k++;
    }
    while (j <= high)		 
    {
        arr1[k] = arr[j];
        j++; k++;
    }
    for (k = 0, i = low; i <= high; k++, i++) 
        arr[i] = arr1[k];
}

//基数排序的辅助函数2
int Sort::getMax(const vector<int>& arr) {
    int max = arr[0];
    for (int num : arr) {
        if (num > max) {
            max = num;
        }
    }
    return max;
}

//基数排序的辅助函数1
void Sort::countingSort(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n); 
    int count[10] = { 0 }; 

    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++; 
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
   
    for (int i = n - 1; i >= 0; i--) { 
        output[count[(arr[i] / exp) % 10] - 1] = arr[i]; 
        count[(arr[i] / exp) % 10]--; 
    }

    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// 基数排序实现
void Sort::radixSort(vector<int> arr) {
    int max = getMax(arr);
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(arr, exp);
    }
}