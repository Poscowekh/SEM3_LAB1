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

//sort function functor class
template<typename T>
class SortFunction {
public:
    using Sequence = Sequence<T>*;
    using Comparator = Comparator<T>;
    using Sort = Sequence (*)(Sequence&, Comparator);

private:
    Sort sort = 0;
    std::string _name = "name undefined";

    SortFunction() = delete;
    SortFunction(const SortFunction&) = delete;

public:
    SortFunction(const std::string& _name, Sort _sort) : sort(_sort), _name(_name) {};
    SortFunction(SortFunction&& other) : sort(other.sort), _name(other._name) {};

    const std::string& name() const{
        return _name;
    };

    Sequence operator()(Sequence& sequence, Comparator comparator = StdComparator<T>) const{
        sort(sequence, comparator);
    };

    ~SortFunction(){
        sort = 0;
    };
};

//swaps
template<typename T> void _swap(T& first, T& second){
    T tmp = first;
    first = second;
    second = tmp;
};
/*template<typename T> void _swap(T* first, T* second){
    T* tmp = (T*)malloc(sizeof(T));
    memcpy(tmp, first, sizeof(T));
    memcpy(first, second, sizeof(T));
    memcpy(second, tmp, sizeof(T));
    free(tmp);
};*/
template<typename T> void _swap(Iterator<T>& first, Iterator<T>& second){
    _swap(*first, *second);
};
template<typename T> void _swap(Iterator<T>& iter, T& value){
    _swap(*iter, value);
};
template<typename T> void _swap(T& value, Iterator<T>& iter){
    _swap(value, *iter);
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

//bs
template<typename T>
int __bin_search(Sequence<T>* sequence, const T& member, const int left, const int right){
    int middle = (right + left) / 2;
    if(sequence->get(middle) == member)
        return middle;
    else if(right == middle || middle == left)
        return -1;
    else if(member < sequence->get(middle))
        return __bin_search(sequence, member, left, middle);
    else
        return __bin_search(sequence, member, middle, right);
};
template<typename T>
Iterator<T> __bin_search(Sequence<T>* sequence, const Iterator<T>& member_iter, const Iterator<T>& left, const Iterator<T>& right){
    if(right == member_iter)
        return right;
    else if(left == member_iter)
        return left;

    int middle = (right + left) / 2;
    Iterator<T> middle_iter = left + middle;

    if(*middle_iter == *member_iter)
        return middle_iter;
    else if(*member_iter < *middle_iter)
        return __bin_search(sequence, member_iter, left, middle_iter);
    else if(*member_iter > *middle_iter)
        return __bin_search(sequence, member_iter, middle_iter, right);
    else
        return sequence->end();
};

template<typename T> int _bin_search(Sequence<T>* sequence, const T& member){
    return __bin_search(sequence, member, 0, sequence->size() - 1);
};
template<typename T> Iterator<T> _bin_search(Sequence<T>* sequence, const Iterator<T>& member_iter){
    return __bin_search(sequence, member_iter, sequence->begin(), sequence->at(sequence->size() - 1));
};

#endif // BASE_FOR_SORTS_HPP
