#include "SortAlgorithm.h"
#include <algorithm>

void SortAlgorithm::addFrame(std::vector<SortState> &frames,
                             const std::vector<int> &arr, int active1,
                             int active2, int pivot,
                             const std::vector<bool> &isSorted,
                             const QString &desc, bool isSwap) {
  SortState state(arr);
  state.active1 = active1;
  state.active2 = active2;
  state.pivot = pivot;
  state.isSorted = isSorted;
  state.description = desc;
  state.isSwap = isSwap;

  int prevSwaps = frames.empty() ? 0 : frames.back().swapCount;
  int prevCompares = frames.empty() ? 0 : frames.back().compareCount;

  if (isSwap) {
    state.swapCount = prevSwaps + 1;
    state.compareCount = prevCompares;
  } else {
    state.swapCount = prevSwaps;
    // If we're highlighting elements but not swapping, it's likely a
    // comparison/access
    if (active1 != -1 || active2 != -1) {
      state.compareCount = prevCompares + 1;
    } else {
      state.compareCount = prevCompares;
    }
  }

  frames.push_back(state);
}

QString SortAlgorithm::getAlgorithmName(SortType type) {
  switch (type) {
  case SortType::Insertion:
    return "直接插入排序";
  case SortType::BinaryInsertion:
    return "折半插入排序";
  case SortType::Shell:
    return "希尔排序";
  case SortType::Bubble:
    return "冒泡排序";
  case SortType::Quick:
    return "快速排序";
  case SortType::Selection:
    return "直接选择排序";
  case SortType::Heap:
    return "堆排序";
  case SortType::Merge:
    return "归并排序";
  case SortType::Radix:
    return "基数排序";
  default:
    return "未知的排序算法";
  }
}

std::vector<SortState>
SortAlgorithm::generateFrames(SortType type,
                              const std::vector<int> &initialArray) {
  std::vector<SortState> frames;
  // initial frame
  addFrame(frames, initialArray, -1, -1, -1,
           std::vector<bool>(initialArray.size(), false), "初始状态");

  switch (type) {
  case SortType::Insertion:
    insertionSort(initialArray, frames);
    break;
  case SortType::BinaryInsertion:
    binaryInsertionSort(initialArray, frames);
    break;
  case SortType::Shell:
    shellSort(initialArray, frames);
    break;
  case SortType::Bubble:
    bubbleSort(initialArray, frames);
    break;
  case SortType::Quick:
    quickSort(initialArray, frames);
    break;
  case SortType::Selection:
    selectionSort(initialArray, frames);
    break;
  case SortType::Heap:
    heapSort(initialArray, frames);
    break;
  case SortType::Merge:
    mergeSort(initialArray, frames);
    break;
  case SortType::Radix:
    radixSort(initialArray, frames);
    break;
  }

  // final frame
  addFrame(frames, frames.back().array, -1, -1, -1,
           std::vector<bool>(initialArray.size(), true), "排序完成");
  return frames;
}

void SortAlgorithm::insertionSort(std::vector<int> arr,
                                  std::vector<SortState> &frames) {
  int n = arr.size();
  std::vector<bool> isSorted(n, false);
  isSorted[0] = true;
  for (int i = 1; i < n; i++) {
    int key = arr[i];
    int j = i - 1;
    addFrame(frames, arr, i, j, -1, isSorted, QString("选择元素 %1").arg(key));
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      addFrame(frames, arr, j + 1, j, -1, isSorted,
               QString("移动元素 %1").arg(arr[j]), true);
      j = j - 1;
    }
    arr[j + 1] = key;
    isSorted[i] = true;
    addFrame(frames, arr, j + 1, -1, -1, isSorted,
             QString("插入元素 %1").arg(key), true);
  }
}

void SortAlgorithm::binaryInsertionSort(std::vector<int> arr,
                                        std::vector<SortState> &frames) {
  int n = arr.size();
  std::vector<bool> isSorted(n, false);
  isSorted[0] = true;
  for (int i = 1; i < n; i++) {
    int key = arr[i];
    int left = 0;
    int right = i - 1;
    addFrame(frames, arr, i, -1, -1, isSorted,
             QString("选择元素 %1，准备折半查找").arg(key));
    while (left <= right) {
      int mid = left + (right - left) / 2;
      addFrame(frames, arr, i, mid, -1, isSorted,
               QString("查找中，比较 %1 和 %2").arg(key).arg(arr[mid]));
      if (key < arr[mid])
        right = mid - 1;
      else
        left = mid + 1;
    }
    for (int j = i - 1; j >= left; j--) {
      arr[j + 1] = arr[j];
      addFrame(frames, arr, j + 1, j, -1, isSorted,
               QString("移动元素 %1").arg(arr[j]), true);
    }
    arr[left] = key;
    isSorted[i] = true;
    addFrame(frames, arr, left, -1, -1, isSorted,
             QString("插入元素 %1").arg(key), true);
  }
}

void SortAlgorithm::shellSort(std::vector<int> arr,
                              std::vector<SortState> &frames) {
  int n = arr.size();
  std::vector<bool> isSorted(n, false);
  for (int gap = n / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < n; i += 1) {
      int temp = arr[i];
      int j;
      addFrame(frames, arr, i, i - gap, -1, isSorted,
               QString("增量 %1: 选择元素 %2").arg(gap).arg(temp));
      for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
        arr[j] = arr[j - gap];
        addFrame(frames, arr, j, j - gap, -1, isSorted,
                 QString("移动元素 %1").arg(arr[j]));
      }
      arr[j] = temp;
      addFrame(frames, arr, j, -1, -1, isSorted,
               QString("插入元素 %1").arg(temp));
    }
  }
}

void SortAlgorithm::bubbleSort(std::vector<int> arr,
                               std::vector<SortState> &frames) {
  int n = arr.size();
  std::vector<bool> isSorted(n, false);
  bool swapped;
  for (int i = 0; i < n - 1; i++) {
    swapped = false;
    for (int j = 0; j < n - i - 1; j++) {
      addFrame(frames, arr, j, j + 1, -1, isSorted,
               QString("比较 %1 和 %2").arg(arr[j]).arg(arr[j + 1]));
      if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
        swapped = true;
        addFrame(frames, arr, j, j + 1, -1, isSorted,
                 QString("交换 %1 和 %2").arg(arr[j]).arg(arr[j + 1]), true);
      }
    }
    isSorted[n - i - 1] = true;
    if (!swapped)
      break;
  }
}

void SortAlgorithm::quickSort(std::vector<int> arr,
                              std::vector<SortState> &frames) {
  std::vector<bool> isSorted(arr.size(), false);
  quickSortHelper(arr, 0, arr.size() - 1, frames, isSorted);
}

void SortAlgorithm::quickSortHelper(std::vector<int> &arr, int low, int high,
                                    std::vector<SortState> &frames,
                                    std::vector<bool> &isSorted) {
  if (low <= high) {
    int pivot = arr[high];
    addFrame(frames, arr, -1, -1, high, isSorted,
             QString("选择主元 %1").arg(pivot));
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
      addFrame(frames, arr, j, high, high, isSorted,
               QString("比较 %1 和主元 %2").arg(arr[j]).arg(pivot));
      if (arr[j] < pivot) {
        i++;
        std::swap(arr[i], arr[j]);
        addFrame(frames, arr, i, j, high, isSorted,
                 QString("交换 %1 和 %2").arg(arr[i]).arg(arr[j]), true);
      }
    }
    std::swap(arr[i + 1], arr[high]);
    addFrame(frames, arr, i + 1, high, i + 1, isSorted,
             QString("主元归位到 %1").arg(i + 1), true);
    int pi = i + 1;
    isSorted[pi] = true;
    quickSortHelper(arr, low, pi - 1, frames, isSorted);
    quickSortHelper(arr, pi + 1, high, frames, isSorted);
  }
}

void SortAlgorithm::selectionSort(std::vector<int> arr,
                                  std::vector<SortState> &frames) {
  int n = arr.size();
  std::vector<bool> isSorted(n, false);
  for (int i = 0; i < n - 1; i++) {
    int min_idx = i;
    for (int j = i + 1; j < n; j++) {
      addFrame(frames, arr, j, min_idx, -1, isSorted,
               QString("寻找最小值，当前最小 %1，比较 %2")
                   .arg(arr[min_idx])
                   .arg(arr[j]));
      if (arr[j] < arr[min_idx]) {
        min_idx = j;
      }
    }
    if (min_idx != i) {
      std::swap(arr[min_idx], arr[i]);
      addFrame(frames, arr, i, min_idx, -1, isSorted,
               QString("交换 %1 和 %2").arg(arr[i]).arg(arr[min_idx]), true);
    }
    isSorted[i] = true;
  }
}

void SortAlgorithm::heapify(std::vector<int> &arr, int n, int i,
                            std::vector<SortState> &frames,
                            std::vector<bool> &isSorted) {
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;

  if (l < n) {
    addFrame(frames, arr, l, largest, -1, isSorted,
             QString("堆化: 比较 %1 和 %2").arg(arr[l]).arg(arr[largest]));
    if (arr[l] > arr[largest])
      largest = l;
  }
  if (r < n) {
    addFrame(frames, arr, r, largest, -1, isSorted,
             QString("堆化: 比较 %1 和 %2").arg(arr[r]).arg(arr[largest]));
    if (arr[r] > arr[largest])
      largest = r;
  }

  if (largest != i) {
    std::swap(arr[i], arr[largest]);
    addFrame(frames, arr, i, largest, -1, isSorted,
             QString("堆化: 交换 %1 和 %2").arg(arr[i]).arg(arr[largest]),
             true);
    heapify(arr, n, largest, frames, isSorted);
  }
}

void SortAlgorithm::heapSort(std::vector<int> arr,
                             std::vector<SortState> &frames) {
  int n = arr.size();
  std::vector<bool> isSorted(n, false);
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(arr, n, i, frames, isSorted);
  }
  for (int i = n - 1; i > 0; i--) {
    std::swap(arr[0], arr[i]);
    isSorted[i] = true;
    addFrame(frames, arr, 0, i, -1, isSorted,
             QString("提取堆顶最大的元素 %1").arg(arr[i]), true);
    heapify(arr, i, 0, frames, isSorted);
  }
}

void SortAlgorithm::mergeSortHelper(std::vector<int> &arr, int left, int right,
                                    std::vector<SortState> &frames,
                                    std::vector<bool> &isSorted) {
  if (left >= right)
    return;
  int mid = left + (right - left) / 2;
  mergeSortHelper(arr, left, mid, frames, isSorted);
  mergeSortHelper(arr, mid + 1, right, frames, isSorted);

  int n1 = mid - left + 1;
  int n2 = right - mid;
  std::vector<int> L(n1), R(n2);
  for (int i = 0; i < n1; i++)
    L[i] = arr[left + i];
  for (int j = 0; j < n2; j++)
    R[j] = arr[mid + 1 + j];

  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    addFrame(frames, arr, k, -1, -1, isSorted,
             QString("归并元素 %1").arg(arr[k]));
    k++;
  }
  while (i < n1) {
    arr[k] = L[i];
    addFrame(frames, arr, k, -1, -1, isSorted,
             QString("归并元素 %1").arg(arr[k]));
    i++;
    k++;
  }
  while (j < n2) {
    arr[k] = R[j];
    addFrame(frames, arr, k, -1, -1, isSorted,
             QString("归并元素 %1").arg(arr[k]));
    j++;
    k++;
  }
}

void SortAlgorithm::mergeSort(std::vector<int> arr,
                              std::vector<SortState> &frames) {
  std::vector<bool> isSorted(arr.size(), false);
  mergeSortHelper(arr, 0, arr.size() - 1, frames, isSorted);
}

void SortAlgorithm::radixSort(std::vector<int> arr,
                              std::vector<SortState> &frames) {
  int n = arr.size();
  if (n == 0)
    return;
  std::vector<bool> isSorted(n, false);
  int m = *std::max_element(arr.begin(), arr.end());
  for (int exp = 1; m / exp > 0; exp *= 10) {
    std::vector<int> output(n);
    int i, count[10] = {0};
    for (i = 0; i < n; i++)
      count[(arr[i] / exp) % 10]++;
    for (i = 1; i < 10; i++)
      count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--) {
      output[count[(arr[i] / exp) % 10] - 1] = arr[i];
      count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++) {
      arr[i] = output[i];
      addFrame(frames, arr, i, -1, -1, isSorted,
               QString("基数排序: 更新位 %1 的元素 %2").arg(exp).arg(arr[i]));
    }
  }
}
