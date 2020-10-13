#pragma once
#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP
#include "../List/_list.hpp"
#include "../Array/_array.hpp"
#include "../InterfaceIterator.hpp"

template<typename T>
class Sequence{
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using value = T;
    using iterator = Iterator<T>;
    using const_iterator = const Iterator<T>;

public:
    virtual int size() const = 0;
    virtual void clear() = 0;
    virtual bool empty() const = 0;

    virtual reference front() = 0;
    virtual value front() const = 0;
    virtual reference back() = 0;
    virtual value back() const = 0;
    virtual reference get(const int index) = 0;
    virtual value get(const int index) const = 0;

    virtual void set(const int index, const_reference data) = 0;

    virtual void append(const_reference data) = 0;    //to tail
    virtual void append(const_pointer data, const int count = 1){
        for(int i = 0; i < count; i++)
            append(*(data + i));
    };
    virtual void prepend(const_reference data) = 0;   //to first
    virtual void prepend(const_pointer data, const int count = 1){
        for(int i = 0; i < count; i++)
            prepend(*(data + i));
    };

    virtual void insert_at(const_reference data, const int index) = 0;
    virtual void insert_at(const_pointer data, const int index){
        insert_at(*data, index);
    };
    virtual void remove_at(const int index) = 0;

    virtual Sequence* sub_sequence(const int from, const int to) const = 0;

    virtual void concate(const Sequence* other) = 0;
    virtual void concate(const Sequence& other) = 0;

    virtual Sequence* get_concated(const Sequence* other) const = 0;
    virtual Sequence* get_concated(const Sequence& other) const = 0;

    virtual Sequence* get_copy() const = 0;

    virtual void copy(const_pointer data, const int count) = 0;

    virtual reference operator[](const int index) = 0;
    virtual value operator[](const int index) const = 0;

    virtual operator std::string() const = 0;
    virtual operator pointer() const{
        pointer result = pointer(malloc(sizeof(T) * size()));
        for(int i = 0; i < size(); i++)
            *(result + i) = get(i);
        return result;
    };

    virtual Sequence& operator+(const Sequence& other){
        return dynamic_cast<Sequence&>(*get_concated(other));
    };
    virtual Sequence* operator+(const Sequence* other){
        return get_concated(other);
    };

    virtual Sequence& operator=(const Sequence& other) = 0;
    virtual Sequence* operator=(const Sequence* other) = 0;
    virtual Sequence* operator=(std::initializer_list<T> list) = 0;

    virtual ~Sequence(){};

    virtual iterator begin() = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator cbegin() const = 0;

    virtual iterator end() = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cend() const = 0;

    virtual iterator at(const int index) = 0;
    virtual const_iterator at(const int index) const = 0;
    virtual const_iterator cat(const int index) const = 0;
};

/* IMPOSSIBLE
template<typename T>
Sequence<T>* operator+(const T& value, const Sequence<T>* sequence){
    Sequence<T>* result;
    *result = *sequence;
    result->prepend(value);
    return result;
};
template<typename T>
Sequence<T>* operator+(const T& value, const Sequence<T>& sequence){
    Sequence<T>* result;
    *result = sequence;
    result->prepend(value);
    return result;
};

template<typename T>
Sequence<T>& operator+=(const T& value, Sequence<T>* sequence){
    Sequence<T> result = Sequence<T>(sequence);
    result->prepend(value);
    return result;
};
template<typename T>
Sequence<T>& operator+=(const T& value, Sequence<T>& sequence){
    sequence.prepend(value);
    return sequence;
};*/

template<typename T>
std::ostream& operator<<(std::ostream& out, const Sequence<T>* sequence){
    out << "Sequence (size = " << sequence->size() << "):";
    if(sequence->size() == 0)
        out << " [ ];";
    else {
        out << "\n[ ";
        for(auto i = 0; i < sequence->size() - 1; i++)
            out << sequence->get(i) << ", ";
        out << sequence->back() << " ];";
    };
    out << '\n';
    return out;
};
template<typename T>
std::ostream& operator<<(std::ostream& out, const Sequence<T>& sequence){
    return (out << &sequence);
};

template<typename T>
std::istream& operator>>(std::istream& in, Sequence<T>* sequence){
    // WARNING! IN C++ THERE IS NO WAY TO CHECK INITIALIZATION!!!
    // if sequence pointer is uninitialized it may break!
    //Dut to it being a base class it cannot be constructed and so cannot be initilized
    /*if(!(sequence != 0) && !(sequence == 0))
        throw std::runtime_error("Sequence exception: sequence uninitialized");*/
    int count = 0;
    sequence->clear();
    in >> count;
    T tmp = T();
    for(int i = 0; i < count; i++){
        in >> tmp;
        sequence->append(tmp);
    };
    return in;
};
template<typename T>
std::istream& operator>>(std::istream& in, Sequence<T>& sequence){
    return (in >> &sequence);
};

#endif // SEQUENCE_HPP
