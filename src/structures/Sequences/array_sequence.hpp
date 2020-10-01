#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H
#include "_sequence.hpp"
#include "../List/_list.hpp"
#include "../Array/_array.hpp"

template<typename T>
class ArraySequence : public Sequence<T>{
private:
    using Array = Array<T>;
    using List = List<T>;
    using Sequence = Sequence<T>;
    using iterator = BaseIterator<T>*;
    using const_iterator = const BaseIterator<T>*;

    using value = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    Array* _array;

public:
    ArraySequence() : _array(new Array()) {};
    ArraySequence(const T* data, const int count) : _array(new Array(data, count)) {};

    ArraySequence(const Array* array) : _array(new Array(array)) {};
    ArraySequence(const Array& array) : ArraySequence(&array) {};
    ArraySequence(Array&& array) : ArraySequence(&array) {
        array._data = 0;
    };

    ArraySequence(const ArraySequence& other) : _array(new Array(other._array)) {};
    ArraySequence(const ArraySequence* other) : _array(new Array(other->_array)) {};

    int size() const{
        return _array->size();
    };
    void clear(){
        if(this != 0)
            _array->clear();
    };
    bool empty() const{
        if(_array->size() > 0)
            return true;
        return false;
    };

    T& front(){
        return _array->front();
    };
    T front() const{
        return _array->front();
    };
    T& get(const int index){
        return _array->get(index);
    };
    T get(const int index) const{
        return _array->get(index);
    };
    T& back(){
        return _array->back();
    };
    T back() const{
        return _array->back();
    };

    void append(const T& data){
        _array->push_back(&data);
    };
    void Prepend(const T& data){
        _array->PushFront(&data);
    };
    void InsertAt(const T& data, const int index){
        _array->InsertAt(&data, index);
    };
    void RemoveAt(const int index){
        _array->RemoveAt(index);
    };

    /*Array* DataPointer(){//why?
        return _array;
    };*/

    Sequence* subsequence(const int from, const int to) const{
        Sequence* result = new ArraySequence();
        result->_array = _array->subarray(from, to);
        result->length = from - to + 1;
        return result;
    };

    void concate(const Sequence* other){
        auto iter = other->cbegin();
        auto end = other->cend();
        while(iter != end){

        }
    };
    void concate(const Sequence& other){

    };
    ArraySequence& Concate(const ArraySequence& other){//wtf is going on
        _array->CopyToArray(other->_array->FrontPointer(), 0, other->_array->GetLength());
        return *this;
    };
    ArraySequence& GetCopy() const{
        ArraySequence result(*this);
        return result;
    };
    ArraySequence& CopyTo(ArraySequence& destination, const int from, const int to) const{
        for(int i = from; i <= to; i++)
            destination.Append((*this)[i]);
        return destination;
    };

    T& operator[](const int index){
        return get(index);
    };
    ArraySequence& operator=(const ArraySequence& other){
        if(*this != other)
            *this = ArraySequence(other);
        return *this;
    };
    bool operator!=(const ArraySequence& other) const{
        return (*_array) != *(other._array);
    }
    ArraySequence& operator+(const ArraySequence& other) const{
        ArraySequence result(*this);
        CopyTo(result, 0, _array->length - 1);
        return result;
    };
    void operator+=(const ArraySequence& other){
        *this = *this + other;
    }
    ArraySequence& operator+(const T& data) const{
        ArraySequence result(*this);
        result.Append(data);
        return result;
    }
    void operator+=(const T& data){
        *this = *this + data;
    }

    ~ArraySequence(){
        delete _array;
    };
};

#endif // ARRAYSEQUENCE_H
