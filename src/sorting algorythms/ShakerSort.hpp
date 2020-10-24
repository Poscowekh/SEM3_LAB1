#ifndef SHAKERSORT_HPP
#define SHAKERSORT_HPP
#include "base_for_sorts.hpp"

template<typename T>
bool _right_sort(Sequence<T>*& sequence, Comparator<T> comparator, int& left, const int& right){
    bool _swap_flag = false;
    auto iter1 = sequence->at(right);
    auto iter2 = --(sequence->at(right));
    for(int j = right; j > left; --j){
        if(comparator(*iter1, *iter2)){
            _swap_flag = true;
            _swap(iter1, iter2);
        };
        --iter2;
        --iter1;
    };
    ++left;
    return _swap_flag;
};

template<typename T>
bool _left_sort(Sequence<T>*& sequence, Comparator<T> comparator, const int& left, int& right){
    bool _swap_flag = false;
    auto iter1 = sequence->at(left);
    auto iter2 = ++(sequence->at(left));
    for(int j = left; j < right; ++j){
        if(comparator(*iter2, *iter1)){
            _swap(iter1, iter2);
            _swap_flag = true;
        };
        ++iter1;
        ++iter2;
    };
    --right;
    return _swap_flag;
};

template<typename T>
Sequence<T>* ShakerSort(Sequence<T>*& sequence, Comparator<T> comparator = StdComparator<T>){
    if(sequence == 0 || sequence->size() < 2)
        return sequence;
    int left = 0, right = sequence->size() - 1;
    while(left < right){
        if(!_right_sort(sequence, comparator, left, right))
            break;
        if(!_left_sort(sequence, comparator, left, right))
            break;
    };
    return sequence;
};

#endif // SHAKERSORT_HPP
