#ifndef BUBBLESORT_HPP
#define BUBBLESORT_HPP
#include "base_for_sorts.hpp"

template<typename T>
Sequence<T>* BubbleSort(Sequence<T>*& sequence, Comparator<T> comparator = StdComparator<T>){
    if(sequence == 0 || sequence->size() < 2)
        return sequence;
    for(int i = sequence->size() - 1; i > 0; i--){
        bool _swap_flag = false;
        auto iter1 = sequence->begin();
        auto iter2 = ++(sequence->begin());
        for(int j = 0; j < i; ++j){
            if(comparator(*iter2, *iter1)){
                _swap(iter1, iter2);
                _swap_flag = true;
            };
            ++iter1;
            ++iter2;
        };
        if(!_swap_flag)
            break;
    };
    return sequence;
};

#endif // BUBBLESORT_HPP
