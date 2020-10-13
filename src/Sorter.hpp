#ifndef SORTER_HPP
#define SORTER_HPP
#include <chrono>
#include <iostream>
#include "Structures.hpp"
#include "Sorts.hpp"

template<typename SortFunc> class Sorter : public Array<SortFunc>{
private:
    using _array = Array<SortFunc>;

public:
    Sorter() : _array() {};
    Sorter(SortFunc func) : _array(&func, 1) {};

    Sorter(const Sorter* other) = delete;
    Sorter(Sorter&& other) = delete;
    Sorter(const Sorter& other) = delete;

    void add_sort(SortFunc func){
        Sorter::push_back(func);
    };


    template<typename T>
    Sequence<T>* get_sorted(const Sequence<T>* sequence, Comparator<T> comparator = StdComparator, bool print_time = false){
        Sequence<T>* copy = sequence->get_copy();
        sort(copy);
        return copy;
    };
    template<typename T>
    Sequence<T>* get_sorted(const Sequence<T>& sequence, Comparator<T> comparator = StdComparator, bool print_time = false){
        return get_sorted(&sequence);
    };

    template<typename T>
    Sequence<T>* operator()(const Sequence<T>* sequence, Comparator<T> comparator = StdComparator, bool print_time = false){
        time_t begin = time(0);
        Sequence<T>* result = get_sorted(result);
        if(print_time){
            time_t end = time(0);
            std::cout << "Time taken: " << end - begin << " seconds/n";
        };
        return result;
    };
    template<typename T>
    Sequence<T>* operator()(const Sequence<T>& sequence, Comparator<T> comparator = StdComparator, bool print_time = false){
        return (*this)(&sequence, comparator, print_time);
    };

    Sorter& operator=(const Sorter& other){
        if(this != &other)
            ;
            //Sorter::_array = other;
        return *this;
    };

    ~Sorter(){
        ~_array();
    };
};

#endif // SORTER_HPP
