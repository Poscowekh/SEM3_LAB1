#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP
#include "base_for_sorts.hpp"

template<typename T>
void QuickSort(Sequence<T>* sequence, Comparator<T> comparator = StdComparator<T>){
    if(sequence == 0 || sequence->size() < 2)
        return;
    _quicksort(sequence, comparator, 0, sequence->size() - 1);
};

template<typename T>
int _partition(Sequence<T>* sequence, Comparator<T> comparator, int left, int right){
    T x = sequence->get(right);
    int i = left - 1;
    auto iter1 = sequence->at(left), iter2 = iter1;
    for(int j = left; j < right; j++, iter1++){
        if(comparator(*iter1, x) || *iter1 == x){
            if(++i > left)
                iter2++;
            swap(iter1, iter2);
        };
    };
    if(i < left)
        swap(iter2, sequence->get(right));
    else
        swap(++iter2, sequence->get(right));
    return ++i;
};

template<typename T>
void _quicksort(Sequence<T>* sequence, Comparator<T> comparator, int left, int right){
    if(left < right){
        int q = _partition(sequence, comparator, left, right);
        _quicksort(sequence, comparator, left, q - 1);
        _quicksort(sequence, comparator, q + 1, right);
    };
};


//no need
template<typename T>
void _combination(Sequence<T>* sequence, int left, int right);

#endif // QUICKSORT_HPP
