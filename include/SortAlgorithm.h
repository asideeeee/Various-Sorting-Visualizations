#ifndef SORTALGORITHM_H
#define SORTALGORITHM_H

#include "SortState.h"
#include <QString>
#include <vector>

class SortAlgorithm {
public:
  static std::vector<SortState>
  generateFrames(SortType type, const std::vector<int> &initialArray);
  static QString getAlgorithmName(SortType type);

private:
  static void insertionSort(std::vector<int> arr,
                            std::vector<SortState> &frames);
  static void binaryInsertionSort(std::vector<int> arr,
                                  std::vector<SortState> &frames);
  static void shellSort(std::vector<int> arr, std::vector<SortState> &frames);
  static void bubbleSort(std::vector<int> arr, std::vector<SortState> &frames);
  static void quickSort(std::vector<int> arr, std::vector<SortState> &frames);
  static void quickSortHelper(std::vector<int> &arr, int low, int high,
                              std::vector<SortState> &frames,
                              std::vector<bool> &isSorted);
  static void selectionSort(std::vector<int> arr,
                            std::vector<SortState> &frames);
  static void heapSort(std::vector<int> arr, std::vector<SortState> &frames);
  static void heapify(std::vector<int> &arr, int n, int i,
                      std::vector<SortState> &frames,
                      std::vector<bool> &isSorted);
  static void mergeSort(std::vector<int> arr, std::vector<SortState> &frames);
  static void mergeSortHelper(std::vector<int> &arr, int left, int right,
                              std::vector<SortState> &frames,
                              std::vector<bool> &isSorted);
  static void radixSort(std::vector<int> arr, std::vector<SortState> &frames);

  static void addFrame(std::vector<SortState> &frames,
                       const std::vector<int> &arr, int active1, int active2,
                       int pivot, const std::vector<bool> &isSorted,
                       const QString &desc, bool isSwap = false);
};

#endif // SORTALGORITHM_H