#ifndef ARRAY_ITERATOR_HPP
#define ARRAY_ITERATOR_HPP
#include "../_libs.hpp"

template<typename value>
class ArrayIterator : public BaseIterator<value>{
private:
    using reference = value&;
    using const_reference = const value&;
    using pointer = value*;
    using const_pointer = const value*;
    using base_iterator = BaseIterator<value>*;

    pointer _ptr;

    const_pointer cptr() const{
        if(_is_end())
            throw std::runtime_error("\nArray iterator exception: dereferencing end iterator");
        return _ptr;
    };

    reference ref(){
        if(_is_end())
            throw std::runtime_error("\nArray iterator exception: dereferencing end iterator");
        return *_ptr;
    };
    const_reference cref() const{
        if(_is_end())
            throw std::runtime_error("\nArray iterator exception: dereferencing end iterator");
        return *_ptr;
    };

    value val() const{
        if(_is_end())
            throw std::runtime_error("\nArray iterator exception: dereferencing end iterator");
        return *_ptr;
    };

    bool _is_end() const{
        if(_ptr == 0)
            return true;
        return false;
    };

    ArrayIterator* _copy() const{
        return new ArrayIterator(this);
    };

public:
    ArrayIterator() = delete;
    ArrayIterator(pointer data_ptr) : _ptr(data_ptr) {};
    ArrayIterator(const_pointer data_ptr){
        _ptr = data_ptr;
    };
    ArrayIterator(const ArrayIterator* other) : _ptr(other->_ptr) {};
    ArrayIterator(const ArrayIterator& other) : _ptr(other._ptr) {};
    ArrayIterator(ArrayIterator&& other) : _ptr(other._ptr) {
        other._ptr = 0;
    };

    const ArrayIterator& operator=(const ArrayIterator& other) {
        _ptr = other._ptr;
        return *this;
    };
    const ArrayIterator& operator=(ArrayIterator&& other) {
        _ptr = other._ptr;
        other._ptr = 0;
        return *this;
    };
    base_iterator operator=(const base_iterator other) {
        dynamic_cast<BaseIterator<value>&>(*this) = other;
        _ptr = other->cptr();
        return dynamic_cast<base_iterator>(this);
    };

    base_iterator operator++(){
        if(_is_end() || _ptr + 1 == 0)
            throw std::runtime_error("\nArray iterator exception: incrementing end iterator");
        _ptr += 1;
        return dynamic_cast<base_iterator>(this);
    };/*
    base_iterator operator++(int){
        if(_is_end() || _ptr + 1 == 0)
            throw std::runtime_error("\nArray iterator exception: incrementing end iterator");
        base_iterator copy = dynamic_cast<base_iterator>(new ArrayIterator(this));
        _ptr += 1;
        return copy;
    };*/

    base_iterator operator--(){
        if(_ptr - 1 == 0)
            throw std::runtime_error("\nArray iterator exception: decrementing to null-pointing iterator");
        _ptr -= 1;
        return dynamic_cast<base_iterator>(this);
    };/*
    base_iterator operator--(int){
        if(_ptr - 1 == 0)
            throw std::runtime_error("\nArray iterator exception: decrementing to null-pointing iterator");
        base_iterator copy = dynamic_cast<base_iterator>(new ArrayIterator(this));
        _ptr -= 1;
        return copy;
    };*/

    reference operator*(){
        return ref();
    };
    const_reference operator*() const{
        return cref();
    };

    const_pointer operator->() const{
        return cptr();
    };

    base_iterator copy() const{
        return dynamic_cast<base_iterator>(new ArrayIterator(this));
    };

    base_iterator operator+(const int val) const{
       ArrayIterator* result = _copy();
        result->_ptr += val;
        return dynamic_cast<base_iterator>(result);
    };
    base_iterator operator-(const int val) const{
        ArrayIterator* result = _copy();
         result->_ptr -= val;
         return dynamic_cast<base_iterator>(result);
    };

    void operator+=(const int val){
        _ptr += val;
    };
    void operator-=(const int val){
        _ptr -= val;
    };

    int operator-(const ArrayIterator& other) const{
        return std::abs(_ptr - other._ptr);
    };
    int operator-(const BaseIterator<value>& other) const override{
        if(typeid(*this) != typeid(other))
            throw std::runtime_error("\nIterator exception: evaluating distance between iterators of different types");
        return *this - dynamic_cast<const ArrayIterator&>(other);
    };
};


#endif // ARRAY_ITERATOR_HPP
