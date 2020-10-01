#ifndef ARRAY_ITERATOR_HPP
#define ARRAY_ITERATOR_HPP
#include "../_libs.hpp"

template<typename T>
class ArrayIterator : public BaseIterator<T>{
private:
    using reference = T&;
    using pointer = T*;

    T* _ptr;

    T* ptr(){
        return _ptr;
    };
    T* ptr() const{
        return _ptr;
    };

    T& data(){
        return *_ptr;
    };
    T& data() const{
        return *_ptr;
    };

    T val(){
        return *_ptr;
    };
    T val() const{
        return *_ptr;
    };

    bool _is_end() const{
        if(_ptr == 0)
            return true;
        return false;
    };

public:
    ArrayIterator() = delete;
    ArrayIterator(T* data_ptr) : _ptr(data_ptr) {};
    ArrayIterator(const ArrayIterator* other) : _ptr(other->_ptr) {};
    ArrayIterator(const ArrayIterator& other) : _ptr(other._ptr) {};

    void operator++(){
        _ptr += sizeof(T);
    };
    void operator++(int){
        _ptr += sizeof(T);
    };

    void operator--(){
        _ptr -= sizeof(T);
    };
    void operator--(int){
        _ptr -= sizeof(T);
    };

    reference operator*(){
        return *_ptr;
    };
    reference operator*() const{
        return *_ptr;
    };

    pointer operator->(){
        return _ptr;
    };
    const pointer operator->() const{
        return _ptr;
    };

    ~ArrayIterator(){
        _ptr = 0;
    };
};


#endif // ARRAY_ITERATOR_HPP
