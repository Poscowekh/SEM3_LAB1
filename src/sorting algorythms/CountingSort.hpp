#ifndef COUNTINGSORT_HPP
#define COUNTINGSORT_HPP
#include "base_for_sorts.hpp"

template<typename T> T min(Sequence<T>*& sequence, Comparator<T> comparator = StdComparator<T>){
    T min = sequence->front();
    auto iter = sequence->begin(), last = sequence->end();
    while(iter != last){
        if(comparator(*iter, min))
            min = *iter;
        iter++;
    };
    return min;
};

template<typename T> T max(Sequence<T>*& sequence, Comparator<T> comparator = StdComparator<T>){
    T max = sequence->front();
    auto iter = sequence->begin(), last = sequence->end();
    while(iter != last){
        if(!comparator(*iter, max))
            max = *iter;
        iter++;
    };
    return max;
};

template<typename T, typename std::enable_if_t<std::is_integral<T>{} || std::is_floating_point<T>{}, int>::type = 0>
void CountingSort(Sequence<T>*& sequence, Comparator<T> comparator = StdComparator<T>){
    /*T min = min(sequence), max = max(sequence);
    Array<std::pair<T, int> > count_arr = Array<std::pair<T, int> >(int(max - min));
    auto iter = sequence->begin(), last = sequence->end();
    while(iter != last){
        int index = count_arr.find_index(*iter);
        if(index == -1)
            count_arr.push_back(std::make_pair(*iter, 1));
    };*/
};

#endif // COUNTINGSORT_HPP
