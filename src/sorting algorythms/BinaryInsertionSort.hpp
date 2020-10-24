#ifndef BINARYINSERTIONSORT_HPP
#define BINARYINSERTIONSORT_HPP
#include "base_for_sorts.hpp"

template<typename T>
void BinaryInsertionSort(Sequence<T>*& sequence, Comparator<T> comparator = StdComparator<T>){
    Sequence<T>* result = sequence->get_clean_copy();

    auto iter = sequence->begin(),
         last = sequence->end();

    while(iter != last){
        int right = result->size(),
            left = 0,
            index = 0;
        auto index_iter = result->begin();

        while(comparator(left, right)){
            index = (left + right) / 2;

            if(comparator(*iter, *index_iter)){
                left = index + 1;
                index_iter + ((index - left)/ 2);
            } else {
                right = index;
                index_iter - ((right - index) / 2);
            };

            if(right == index)
                break;
        };

        result->insert_at(*iter, index);
        std::cout<<result;

        ++iter;
    };

    //std::cout << result;
    *sequence = *result;

    result = 0;
};

#endif // BINARYINSERTIONSORT_HPP
