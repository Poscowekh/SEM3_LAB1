#ifndef INTERFACEITERATOR_HPP
#define INTERFACEITERATOR_HPP
#include "base_iterator.hpp"

template<typename value, typename iterator_category = std::random_access_iterator_tag>
class Iterator : public std::iterator<iterator_category, value, int>{
private:
    using reference = value&;
    using pointer = value*;
    using const_reference = const value&;
    using const_pointer = const value*;
    using base_iterator = BaseIterator<value>;

    base_iterator* base_iter;

    // input_iterator_tag
    // output_iterator_tag
    // forward_iterator_tag
    // bidirectional_iterator_tag
    // random_access_iterator_tag
    // c++ 20 iter tag

    Iterator(const Iterator* other) : base_iter(other->base_iter->copy()) {};

public:
    Iterator() = delete;
    Iterator(const base_iterator* iter) : base_iter(const_cast<base_iterator*>(iter)) {};
    Iterator(const base_iterator& iter) : base_iter(&iter) {};
    Iterator(const Iterator& other) : base_iter(other.base_iter->copy()) {};
    Iterator(Iterator&& other) : base_iter(other.base_iter) {
        other.base_iter = 0;
    };

    Iterator& operator++(){
        ++(*base_iter);
        return *this;
    };
    Iterator operator++(int){
        Iterator copy = Iterator(this);
        ++(*base_iter);
        return copy;
    };

    Iterator& operator--(){
        --(*base_iter);
        return *this;
    };
    Iterator operator--(int){
        Iterator copy = Iterator(this);
        --(*base_iter);
        return copy;
    };

    const_reference operator*() const{
        return **base_iter;
    };
    reference operator*(){
        return **base_iter;
    };

    /*Iterator& operator=(const value val){
        **base_iter = value(val);
        return *this;
    };*/
    const Iterator& operator=(const Iterator& other){
        base_iter = other.base_iter->copy();
        return *this;
    };
    const Iterator& operator=(Iterator&& other){
        base_iter = other.base_iter;
        other.base_iter = 0;
        return *this;
    };

    bool operator==(const Iterator& other) const{
        return (*base_iter) == (*other.base_iter);
    };
    bool operator!=(const Iterator& other) const{
        return (*base_iter) != (*other.base_iter);
    };

    bool operator>(const Iterator& other) const{
        return (*base_iter) > (*other.base_iter);
    };
    bool operator>=(const Iterator& other) const{
        return (*base_iter) >= (*other.base_iter);
    };

    bool operator<(const Iterator& other) const{
        return (*base_iter) < (*other.base_iter);
    };
    bool operator<=(const Iterator& other) const{
        return (*base_iter) <= (*other.base_iter);
    };

    explicit operator const_reference() const{
        return const_reference(**this);
    };
    explicit operator reference() const{
        return reference(**this);
    };
    explicit operator value() const{
        return value(**this);
    };

    /*void operator+=(const_reference val){
        **this += val;
    };
    void operator+=(const value val){
        **this += val;
    };

    void operator-=(const_reference val){
        **this -= val;
    };
    void operator-=(const value val){
        **this -= val;
    };*/

    Iterator operator+(const int val) const{
        Iterator result = Iterator(this);
        (*result.base_iter) += val;
        return result;
    };
    Iterator operator-(const int val) const{
        Iterator result = Iterator(this);
        (*result.base_iter) -= val;
        return result;
    };

    void operator+=(const int val){
        (*base_iter) += val;
    };
    void operator-=(const int val){
        (*base_iter) -= val;
    };

    /*
    value operator-(const_reference val){
        value result = value(**this);
        result -= val;
        return result;
    };
    value operator-(const value val){
        value result = value(**this);
        result -= val;
        return result;
    };

    friend value operator+(const_reference val, const Iterator& iter){
        value result = value(val);
        result += *iter;
        return result;
    };
    friend value operator+(const value val, const Iterator& iter){
        value result = value(val);
        result += *iter;
        return result;
    };

    friend value operator-(const_reference val, const Iterator& iter){
        value result = value(val);
        result -= *iter;
        return result;
    };
    friend value operator-(const value val, const Iterator& iter){
        value result = value(val);
        result -= *iter;
        return result;
    };*/

    friend std::ostream& operator<<(std::ostream& out, const Iterator& iter){
        out << *iter;
        return out;
    };
    friend std::istream& operator>>(std::istream& in, Iterator& iter){
        value tmp = value();
        in >> tmp;
        *iter = tmp;
        return in;
    };

    int operator-(const Iterator& other) const{
        return (*base_iter - *other.base_iter);
    };

    ~Iterator(){
        delete base_iter;
    };
};

#endif // INTERFACEITERATOR_HPP
