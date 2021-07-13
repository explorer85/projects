#include <QCoreApplication>

/* C++ implementation of QuickSort */
#include <bits/stdc++.h>
#include <functional>
using namespace std;

/* Function to print an array */
void printArray(int arr[], int size) {
  int i;
  for (i = 0; i < size; i++) cout << arr[i] << " ";
  cout << endl;
}

//// A utility function to swap two elements
// void swap(int* a, int* b) {
//  int t = *a;
//  *a = *b;
//  *b = t;
//}

///* This function takes last element as pivot, places
// the pivot element at its correct position in sorted
// array, and places all smaller (smaller than pivot)
// to left of pivot and all greater elements to right
// of pivot */
// int partition(int arr[], int low, int high) {
//  int pivot = arr[high];  // pivot
//  cout << "pivot is " << pivot << " low high" << low << high <<
//  "-------------"
//       << endl;
//  printArray(arr, high + 1);
//  int i = (low - 1);  // Index of smaller element and indicates the right
//                      // position of pivot found so far

//  for (int j = low; j <= high - 1; j++) {
//    cout << "j = " << j << endl;
//    // If current element is smaller than the pivot
//    if (arr[j] < pivot) {
//      i++;  // increment index of smaller element
//      cout << "swap arr[" << i << "] arr[" << j << "] " << arr[i] << " <-> "
//           << arr[j] << endl;
//      swap(&arr[i], &arr[j]);
//    }
//  }
//  cout << "swap arr[i + 1] <-> pivot" << arr[i + 1] << " <-> " << arr[high]
//       << endl;
//  printArray(arr, high + 1);
//  swap(&arr[i + 1], &arr[high]);
//  printArray(arr, high + 1);

//  return (i + 1);
//}

///* The main function that implements QuickSort
// arr[] --> Array to be sorted,
// low --> Starting index,
// high --> Ending index */
// void quickSort(int arr[], int low, int high) {
//  if (low < high) {
//    /* pi is partitioning index, arr[p] is now
//        at right place */
//    int pi = partition(arr, low, high);

//    // Separately sort elements before
//    // partition and after partition
//    quickSort(arr, low, pi - 1);
//    quickSort(arr, pi + 1, high);
//  } else {
//    cout << "RECOIRSIVE FINE" << endl;
//  }
//}

// int main(int argc, char* argv[]) {
//  QCoreApplication a(argc, argv);

//  int arr[] = {3, 7, 8, 5, 2, 1, 9, 5, 4};
//  // int arr[] = {10, 7, 8, 9, 1, 5};
//  int n = sizeof(arr) / sizeof(arr[0]);
//  printArray(arr, n);
//  quickSort(arr, 0, n - 1);
//  cout << "Sorted array: \n";
//  printArray(arr, n);
//  return 0;

//  return a.exec();
//}
std::vector<int> arr = {3, 7, 8, 5, 2, 1, 9, 5, 4};
// std::vector<int> rang = {7, 7, 0, 3, 2, 2, 2, 2, 6, 6, 0, 0};
std::vector<int> rang = {7, 7, 3, 2, 2, 2, 2};

void printList(std::vector<int> arr) {
  for (auto el : arr) cout << el << " ";
  cout << endl;
}

template <class ForwardIt>
void vquickSort(ForwardIt iBegin, ForwardIt iEnd) {
  if (iBegin == iEnd) {
    cout << "recursiend " << endl;
    return;
  }

  auto pivot = *std::next(iBegin, std::distance(iBegin, iEnd) / 2);
  cout << "pivot" << pivot << " beginend" << *iBegin << *iEnd << endl;

  //разделили на 2 диапазона (пивот2 меньше двойки и больше двойки) 1*7 8 5 2 3
  // 9 5 4
  ForwardIt middle1 = std::partition(
      iBegin, iEnd, [pivot](const int& em) { return em < pivot; });
  cout << "middle1 " << std::distance(iBegin, middle1) /*<< " " << *middle1*/
       << endl;
  printList(arr);
  //по во втором диапазоне подняли пивот наверх 1* 2 * 7 8 5 3 9 5 4
  ForwardIt middle2 = std::partition(
      middle1, iEnd, [pivot](const int& em) { return (em == pivot); });
  cout << "middle2 " << std::distance(iBegin, middle2) /*<< " " << *middle2*/
       << endl;
  printList(arr);

  //повторили операцию на диапазоне слева от двойки
  vquickSort(iBegin, middle1);
  //повторили операцию на диапазоне справа от двойки
  vquickSort(middle2, iEnd);
}

// https://www.youtube.com/watch?v=UqVxcO4oNXA
template <class ForwardIt>
ForwardIt vpartition(ForwardIt first, ForwardIt last,
                     std::function<bool(int)> f) {
  for (ForwardIt i = first; i != last; ++i) {
    cout << "iteration " << *i << endl;
    if (f(*i)) {
      cout << "swap " << *i << "<->" << *first << endl;

      std::iter_swap(i, first);
      ++first;
    }
  }
  cout << std::distance(rang.begin(), first) << endl;
  // cout << std::distance(rang.begin(), pivot) << endl;
  printList(rang);
  auto newpivotit = std::find(first, last, 3);
  std::iter_swap(first, newpivotit);

  return first;
}

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  //  cout << "UNSorted array: \n";
  //  printList(arr);
  //  vquickSort(arr.begin(), arr.end());
  //  cout << "Sorted array: \n";
  //  printList(arr);

  cout << "UNSorted array: \n";
  printList(rang);
  auto first =
      vpartition(rang.begin(), rang.end(), [](int i) { return i < 3; });
  cout << std::distance(rang.begin(), first) << "Sorted array: \n";
  printList(rang);

  return 0;

  return a.exec();
}
