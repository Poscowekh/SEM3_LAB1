#ifndef BASE_ITERATOR_HPP
#define BASE_ITERATOR_HPP
#include <iterator>
#include <iostream>

template<typename Value, typename reference = Value&, typename pointer = Value*>
class BaseIterator : std::iterator<std::random_access_iterator_tag, Value, std::size_t, pointer, reference>{
protected:
    virtual reference data() = 0;
    virtual reference data() const = 0;

    virtual pointer ptr() = 0;
    virtual pointer ptr() const = 0;

    virtual Value val() = 0;
    virtual Value val() const = 0;

    virtual bool _is_end() const = 0;

public:
    virtual reference operator*() = 0;
    virtual reference operator*() const = 0;

    virtual pointer operator->() = 0;
    virtual const pointer operator->() const = 0;

    virtual void operator++() = 0;
    virtual void operator++(int) = 0;

    virtual void operator--() = 0;
    virtual void operator--(int) = 0;

    virtual BaseIterator& operator=(const BaseIterator& other){
        if(this != &other)
            data() = other.val();
        return *this;
    };
    virtual BaseIterator* operator=(const BaseIterator* other){
        if(this != other)
            data() = other->val();
        return this;
    };

    virtual operator reference() const{
        return reference(data());
    };
    virtual operator Value() const{
        return Value(val());
    };
    virtual operator pointer() const{
        return ptr();
    };

    virtual void operator+=(const reference value){
        data() += value;
    };
    virtual void operator+=(const BaseIterator* other){
        data() += other->data();
    };
    virtual void operator+=(const BaseIterator& other){
        data() += other.data();
    };

    virtual void operator-=(const reference value){
        data() -= value;
    };
    virtual void operator-=(const BaseIterator* other){
        data() -= other->data();
    };
    virtual void operator-=(const BaseIterator& other){
        data() -= other.data();
    };

    virtual Value operator+(const reference value) const{
        Value result = Value(val());
        result += value;
        return result;
    };
    virtual Value operator+(const BaseIterator* other) const{
        Value result = Value(val());
        result += other->val();
        return result;
    };
    virtual Value operator+(const BaseIterator& other) const{
        Value result = Value(val());
        result += other.val();
        return result;
    };

    virtual Value operator-(const reference value) const{
        Value result = Value(val());
        result -= value;
        return result;
    };
    virtual Value operator-(const BaseIterator* other) const{
        Value result = Value(val());
        result -= other->val();
        return result;
    };
    virtual Value operator-(const BaseIterator& other) const{
        Value result = Value(val());
        result -= other.val();
        return result;
    };

    virtual bool operator==(const BaseIterator* other) const{
        if(other->_is_end()){
            if(_is_end() && (typeid(*this) == typeid(*other)))
                return true;
            return false;
        };
        if(_is_end())
            return false;
        if(ptr() == other->ptr())
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
};

template<typename T>
T operator+(const T& value, const BaseIterator<T>& iter){
    T result = T(value);
    result += *iter;
    return result;
};
template<typename T>
T operator+=(T& value, const BaseIterator<T>& iter){
    value += *iter;
    return value;
};

template<typename T>
T operator-(const T& value, const BaseIterator<T>& iter){
    T result = T(value);
    result -= *iter;
    return result;
};
template<typename T>
T operator-=(T& value, const BaseIterator<T>& iter){
    value -= *iter;
    return value;
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const BaseIterator<T>& iter){
    out << *iter;
    return out;
};
template<typename T>
std::ostream& operator<<(std::ostream& out, const BaseIterator<T>* iter){
    out << **iter;
    return out;
};

#endif // BASE_ITERATOR_HPP
