#ifndef SELECTIONSORT_HPP
#define SELECTIONSORT_HPP
#include "base_for_sorts.hpp"

template<typename T>
Sequence<T>* SelectionSort(Sequence<T>*& sequence, Comparator<T> comparator = StdComparator<T>){
    if(sequence == 0 || sequence->size() < 2)
        return sequence;
    for(int i = 0; i < sequence->size() - 1; i++){
        auto index_iter = sequence->at(i),
             iter = index_iter;
        ++iter;
        for(int j = i + 1; j < sequence->size(); j++, ++iter)
            if(comparator(*iter, *index_iter))
                index_iter = iter;
        _swap(index_iter, sequence->get(i));
    };
    return sequence;
};

#endif // SELECTIONSORT_HPP
