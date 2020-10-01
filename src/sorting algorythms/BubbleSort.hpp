#ifndef BUBBLESORT_HPP
#define BUBBLESORT_HPP
#include "../Structures.hpp"

template<typename T>
using Comparator = bool (&)(const T& first, const T& second);
template<typename T>
using AltComparator = bool (*)(const T* first, const T* second);

template<typename T>
bool StdComparator(const T& first, const T& second){
    return first < second;
};
template<typename T>
bool ReverseComparator(const T& first, const T& second){
    return first > second;
};

template<typename T> void swap(T* first, T* second){
    T* tmp = (T*)malloc(sizeof(T));
    memcpy(tmp, first, sizeof(T));
    memcpy(first, second, sizeof(T));
    memcpy(second, tmp, sizeof(T));
    free(tmp);
};
template<typename T> void swap(T& first, T& second){
    T tmp = T(first);
    first = T(second);
    second = T(tmp);
};

template<typename T>
void BubbleSort(Sequence<T>* sequence, Comparator<T> comparator = StdComparator<T>){
    if(sequence == 0 || sequence->size() < 2)
        return;
    for(int i = 0; i < sequence->size() - 1; i++){
        bool swap_flag = false;
        for(int j = 0; j < sequence->size() - i - 1; j++)
            if(comparator(sequence->get(j + 1), sequence->get(j))){
                swap_flag = true;
                swap(sequence->get(j + 1), sequence->get(j));
            };
        if(!swap_flag)
            break;
    };
};

template<typename T>
void ShakerSort(Sequence<T>* sequence, Comparator<T> comparator = StdComparator<T>){
    if(sequence == 0 || sequence->size() < 2)
        return;
    int left = 0, right = sequence->size() - 1;
    while(left < right){
        bool swap_flag = false;
        for(int j = right; j > left; j--)
            if(comparator(sequence->get(j), sequence->get(j - 1))){
                swap_flag = true;
                swap(sequence->get(j), sequence->get(j - 1));
            };
        if(!swap_flag)
            break;
        right--;
        for(int j = left; j < right; j++)
            if(comparator(sequence->get(j + 1), sequence->get(j)))
                swap(sequence->get(j + 1), sequence->get(j));
        left++;
    };
};

#endif // BUBBLESORT_HPP
