#ifndef SELECTIONSORT_HPP
#define SELECTIONSORT_HPP
#include "base_for_sorts.hpp"

template<typename T>
void SelectionSort(Sequence<T>* sequence, Comparator<T> comparator = StdComparator<T>){
    if(sequence == 0 || sequence->size() < 2)
        return;
    for(int i = 0; i < sequence->size() - 1; i++){
        auto iter = sequence->at(i + 1),
             index_iter = sequence->at(i);
        for(int j = i + 1; j < sequence->size(); j++, iter++)
            if(comparator(*iter, *index_iter))
                index_iter = iter;
        swap(sequence->get(i), *index_iter);
    };
};

#endif // SELECTIONSORT_HPP
