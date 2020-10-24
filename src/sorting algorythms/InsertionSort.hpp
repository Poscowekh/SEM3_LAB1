#ifndef INSERTIONSORT_HPP
#define INSERTIONSORT_HPP
#include "base_for_sorts.hpp"

template<typename T>
Sequence<T>* InsertionSort(Sequence<T>*& sequence, Comparator<T> comparator = StdComparator<T>){
    Sequence<T>* result = sequence->get_clean_copy();
    auto
         iter = sequence->begin(),
         last = sequence->end();

    result->prepend(*iter);
    ++iter;

    while(iter != last) {
        auto input = result->begin(),
             input_end = result->end();
        bool inserted = false;

        int index = 0;
        while(input != input_end){
            if(comparator(*iter, *input)){
                result->insert_at(*iter, index);
                inserted = true;
                break;
            }
            ++index;
            ++input;
        };
        if(!inserted)
            result->append(*iter);
        ++iter;
    };

    return result;
};

#endif // INSERTIONSORT_HPP
