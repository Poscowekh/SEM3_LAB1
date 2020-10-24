#ifndef BASE_ITERATOR_HPP
#define BASE_ITERATOR_HPP
#include <iterator>
#include <iostream>

template<typename value, typename reference = value&, typename pointer = value*>
class BaseIterator{
protected:
    using const_reference = const value&;
    using const_pointer = const value*;

    virtual reference ref() = 0;
    virtual const_reference cref() const = 0;

    virtual const_pointer cptr() const = 0;

    virtual value val() const = 0;

    virtual bool _is_end() const = 0;

public:
    virtual reference operator*() = 0;
    virtual const_reference operator*() const = 0;

    virtual const_pointer operator->() const = 0;

    virtual BaseIterator* operator++() = 0;
    //virtual BaseIterator* operator++(int) = 0;

    virtual BaseIterator* operator--() = 0;
    //virtual BaseIterator* operator--(int) = 0;

    /*virtual BaseIterator& operator=(const BaseIterator& other){
        if(this != &other)
            ref() = other.cref();
        return *this;
    };
    virtual BaseIterator* operator=(const BaseIterator* other){
        if(this != other)
            ref() = other->cref();
        return this;
    };*/

    virtual BaseIterator* copy() const = 0;

    virtual BaseIterator* operator=(const BaseIterator* other){
        if(typeid(*this) != typeid(*other))
            throw std::runtime_error("\nIteratro exception: comparing iterators of different types");
    };

    virtual bool operator==(const BaseIterator* other) const{
        if(typeid(*this) != typeid(*other))
            throw std::runtime_error("\nIteratro exception: comparing iterators of different types");
        if(other->_is_end()){
            if(_is_end())
                return true;
            return false;
        };
        if(_is_end())
            return false;
        if(cptr() == other->cptr())
            return true;
        /*if(val() == other->val())
            return true;*/
        return false;
    };
    virtual bool operator==(const BaseIterator& other) const{
        return (*this == &other);
    };

    virtual bool operator!=(const BaseIterator* other) const{
        return !(*this == other);
    };
    virtual bool operator!=(const BaseIterator& other) const{
        return !(*this == &other);
    };

    virtual bool operator>(const BaseIterator& other) const{
        if(*this - other > 0)
            return true;
        return false;
    };
    virtual bool operator>=(const BaseIterator& other) const{
        if(*this - other >= 0)
            return true;
        return false;
    };

    virtual bool operator<(const BaseIterator& other) const{
        if(*this - other <= 0)
            return true;
        return false;
    };
    virtual bool operator<=(const BaseIterator& other) const{
        if(*this - other <= 0)
            return true;
        return false;
    };

    virtual BaseIterator* operator+(const int val) const = 0;
    virtual BaseIterator* operator-(const int val) const = 0;

    virtual void operator+=(const int val) = 0;
    virtual void operator-=(const int val) = 0;

    virtual int operator-(const BaseIterator& other) const{
        if(typeid(*this) != typeid(other))
            throw std::runtime_error("\nIterator exception: evaluating distance between iterators of different types");
        return cptr() - other.cptr();
    };
};


#endif // BASE_ITERATOR_HPP
