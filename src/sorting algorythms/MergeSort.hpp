#ifndef MERGESORT_HPP
#define MERGESORT_HPP
#include "base_for_sorts.hpp"

template<typename T>
Sequence<T>* _merge_sort(Sequence<T>*& sequence, Comparator<T> comparator = StdComparator<T>){
    if(sequence->size() == 1)
        return sequence->get_copy();

    int divisor = sequence->size() / 2;

    //divising
    Sequence<T>* left_subsequence = sequence->sub_sequence(0, divisor - 1);
    Sequence<T>* left = _merge_sort(left_subsequence, comparator);
    //delete left_subsequence;

    Sequence<T>* right_subsequence = sequence->sub_sequence(divisor, sequence->size() - 1);
    Sequence<T>* right = _merge_sort(right_subsequence, comparator);
    //delete right_subsequence;

    Iterator<T>
            input = sequence->begin(),
            last = sequence->end(),
            left_iter = left->begin(),
            left_last = left->end(),
            right_iter = right->begin(),
            right_last = right->end();
    int size = sequence->size();

    //merging
    for(int i = 0; i < size; ++i, ++input){
        if(left_iter == left_last){
            sequence->copy_range(right_iter, right_last, i);
            break;
        } else if(right_iter == right_last) {
            sequence->copy_range(left_iter, left_last, i);
            break;
        } else {
            if(comparator(*left_iter, *right_iter)) {
                *input = *left_iter;
                ++left_iter;
            } else {
                *input = *right_iter;
                ++right_iter;
            };
        };
    };

    delete left;
    delete right;

    return sequence;
};

template<typename T>
Sequence<T>* MergeSort(Sequence<T>*& sequence, Comparator<T> comparator = StdComparator<T>) {
    if(sequence == 0 || sequence->size() < 2)
        return sequence;
    return _merge_sort(sequence, comparator);
};

#endif // MERGESORT_HPP
