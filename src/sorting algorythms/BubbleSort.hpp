#ifndef BUBBLESORT_HPP
#define BUBBLESORT_HPP
#include "base_for_sorts.hpp"

template<typename T>
void BubbleSort(Sequence<T>* sequence, Comparator<T> comparator = StdComparator<T>){
    if(sequence == 0 || sequence->size() < 2)
        return;
    for(int i = sequence->size() - 1; i > 0; i--){
        bool swap_flag = false;
        auto iter1 = sequence->begin();
        auto iter2 = ++(sequence->begin());
        for(int j = 0; j < i; j++){
            if(comparator(*iter2, *iter1)){
                swap(iter1, iter2);
                swap_flag = true;
            };
            iter1++;
            iter2++;
        };
        if(!swap_flag)
            break;
    };
};

#endif // BUBBLESORT_HPP
