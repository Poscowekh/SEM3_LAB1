#ifndef SORTS_HPP
#define SORTS_HPP
#include "sorting algorythms/BubbleSort.hpp"
#include "sorting algorythms/ShakerSort.hpp"
#include "sorting algorythms/QuickSort.hpp"
#include "sorting algorythms/SelectionSort.hpp"
#include "sorting algorythms/MergeSort.hpp"
#include "sorting algorythms/InsertionSort.hpp"
#include "sorting algorythms/BinaryInsertionSort.hpp"
#include "testing/tester/TestFunctions.hpp"

SortFunction<double> bubble_sort = SortFunction<double>("bubble sort", BubbleSort<double>);
SortFunction<double> shaker_sort = SortFunction<double>("shaker sort", ShakerSort<double>);
SortFunction<double> selection_sort = SortFunction<double>("selection sort", SelectionSort<double>);
SortFunction<double> insertion_sort = SortFunction<double>("insertion sort", InsertionSort<double>);
SortFunction<double> merge_sort = SortFunction<double>("merge sort", MergeSort<double>);
SortFunction<double> quick_sort = SortFunction<double>("quick sort", QuickSort<double>);

#endif // SORTS_HPP
