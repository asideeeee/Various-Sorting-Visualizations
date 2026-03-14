#ifndef SORTSTATE_H
#define SORTSTATE_H

#include <QString>
#include <vector>

struct SortState {
  std::vector<int> array;
  int active1 = -1;
  int active2 = -1;
  int pivot = -1;
  std::vector<bool> isSorted;
  QString description;

  bool isSwap = false;
  int swapCount = 0;
  int compareCount = 0;

  SortState(const std::vector<int> &arr)
      : array(arr), isSorted(arr.size(), false) {}
};

enum class SortType {
  Insertion,
  BinaryInsertion,
  Shell,
  Bubble,
  Quick,
  Selection,
  Heap,
  Merge,
  Radix
};

#endif // SORTSTATE_H
