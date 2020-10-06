#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP
#include "structures/Sequences/list_sequence.hpp"
#include "structures/Sequences/array_sequence.hpp"

using ASeq = ArraySequence<int>;
using LSeq = ListSequence<int>;

template<typename T>
Array<T> array_from_list(const List<T>& list){
    Array<T> array = Array<T>(list.size());
    Iterator
            input = array.begin(),
            iter = list.begin(),
            end = list.end();
    while(iter != end)
        *(input++) = *(iter++);
    return array;
};

template<typename T>
List<T> list_from_array(const Array<T>& array){
    List<T> list = List<T>(array.size());
    Iterator
            input = list.begin(),
            iter = array.begin(),
            end = array.end();
    while(iter != end)
        *(input++) = *(iter++);
    return list;
};

#endif // STRUCTURES_HPP
