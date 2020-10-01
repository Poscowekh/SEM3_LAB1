#ifndef SORTER_HPP
#define SORTER_HPP
#include <chrono>
#include <iostream>
#include "Structures.hpp"
#include "Sorts.hpp"


template<typename SortFunc> class Sorter{
private:
    SortFunc _func;

public:
    Sorter() = delete;
    Sorter(SortFunc func) : _func(func) {};
    Sorter(const Sorter* other) : _func(other->_func) {};

    void SetSort(SortFunc func){
        _func = func;
    };

    template<typename T>
    void Sort(Sequence<T>* sequence, bool print_time = false){
        (*this)(sequence, print_time);
    };
    template<typename T>
    void Sort(Sequence<T>& sequence, bool print_time = false){
        (*this)(&sequence, print_time);
    };

    template<typename T>
    Sequence<T>* get_sorted(const Sequence<T>* sequence, bool print_time = false){};
    template<typename T>
    Sequence<T>* get_sorted(const Sequence<T>& sequence, bool print_time = false){
        return get_sorted(&sequence);
    };

    template<typename T>
    Sequence<T>* operator()(const Sequence<T>* data, bool print_time = false){
        time_t begin = time(0);
        Sequence<T>* result = _sort(data);
        if(print_time){
            time_t end = time(0);
            std::cout << "Time taken: " << end - begin << " seconds/n";
        };
        return result;
    };
    template<typename T>
    Sequence<T>* operator()(const Sequence<T>& data, bool print_time = false){
        time_t begin = time(0);
        Sequence<T>* result = _sort(&data);
        if(print_time){
            time_t end = time(0);
            std::cout << "Time taken: " << end - begin << " seconds/n";
        };
        return result;
    };

    Sorter& operator=(const Sorter&) = default;

    ~Sorter(){
        delete _func;
    };
};

#endif // SORTER_HPP
