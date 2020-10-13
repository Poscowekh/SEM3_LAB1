#ifndef BASE_FOR_SORTS_HPP
#define BASE_FOR_SORTS_HPP
#include "../Structures.hpp"
#include <chrono>

//comparators
template<typename T>
using Comparator = bool (*)(const T& first, const T& second);
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

//swaps
template<typename T> void swap(T* first, T* second){
    T* tmp = (T*)malloc(sizeof(T));
    memcpy(tmp, first, sizeof(T));
    memcpy(first, second, sizeof(T));
    memcpy(second, tmp, sizeof(T));
    free(tmp);
};
template<typename T> void swap(T& first, T& second){
    T tmp = first;
    first = second;
    second = tmp;
};
template<typename T> void swap(Iterator<T>& first, Iterator<T>& second){
    T tmp = *first;
    *first = *second;
    *second = tmp;
};
template<typename T> void swap(Iterator<T>& iter, T& value){
    T tmp = *iter;
    *iter = value;
    value = tmp;
};


//time counting
using m_clock = std::chrono::high_resolution_clock;

template<typename Function, typename ...FuncArgs>
long long _get_time_micro(Function func, FuncArgs... args){
    using namespace std::chrono;
    time_point begin = m_clock::now();
    func(args...);
    milliseconds tmp = std::chrono::duration_cast<milliseconds>(m_clock::now() - begin);
    return static_cast<long long>(tmp.count());
};
template<typename Function, typename ...FuncArgs>
long long _get_time_milli(Function func, FuncArgs... args){
    using namespace std::chrono;
    time_point begin = m_clock::now();
    func(args...);
    microseconds tmp = std::chrono::duration_cast<microseconds>(m_clock::now() - begin);
    return static_cast<long long>(tmp.count());
};

#endif // BASE_FOR_SORTS_HPP
