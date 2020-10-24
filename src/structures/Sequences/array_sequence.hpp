#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H
#include "_sequence.hpp"
#include "../List/_list.hpp"
#include "../Array/_array.hpp"

template<typename value>
class ArraySequence : public Sequence<value>{
private:
    using Array = Array<value>;
    using List = List<value>;
    using Sequence = Sequence<value>;
    using iterator = Iterator<value>;
    using const_iterator = const Iterator<value>;

    using reference = value&;
    using const_reference = const value&;
    using pointer = value*;
    using const_pointer = const value*;

    Array* _array;

    void _resize(const int new_size){
        _array->resize(new_size);
    };

public:
    ArraySequence() : _array(new Array()) {};
    ArraySequence(const int size) : _array(new Array(size)) {};
    ArraySequence(const_pointer data, const int count) : _array(new Array(data, count)) {};
    ArraySequence(const std::initializer_list<value>& list) : _array(new Array(list)) {};
    ArraySequence(const int size, const_reference default_member) : _array(new Array(size, default_member)) {};
    ArraySequence(const int size, const_pointer default_member) : ArraySequence(size, *default_member) {};

    ArraySequence(const Array* array) : _array(new Array(array)) {};
    ArraySequence(const Array& array) : ArraySequence(&array) {};
    ArraySequence(Array&& array) : _array(new Array(std::move(array))) {};

    ArraySequence(const List* list) : ArraySequence(list->size) {
        auto input = begin();
        auto iter = list->begin(), last = list->end();
        while(iter != last){
            *input = *iter;
            ++input;
            ++iter;
        };
    };
    ArraySequence(const List& list) : ArraySequence(&list) {};
    ArraySequence(List&& list) : ArraySequence(list->size) {
        for(int i = 0; i < list.size(); ++i)
            set(i, list.pop_front());
        list.clear();
    };

    ArraySequence(const ArraySequence& other) : _array(new Array(other._array)) {};
    ArraySequence(const ArraySequence* other) : _array(new Array(other->_array)) {};

    ArraySequence(const Sequence* sequence) : ArraySequence(sequence->begin(), sequence->end()) {};
    ArraySequence(const Sequence& sequence) : ArraySequence(&sequence) {};
    ArraySequence(iterator from, iterator to) : _array(new Array(from, to)) {};

    int size() const{
        return _array->size();
    };
    void clear(){
        if(this != 0)
            _array->clear();
    };
    bool empty() const{
        return _array->empty();
    };

    reference front(){
        return _array->front();
    };
    value front() const{
        return _array->front();
    };

    reference get(const int index){
        return _array->get(index);
    };
    value get(const int index) const{
        return _array->get(index);
    };

    reference back(){
        return _array->back();
    };
    value back() const{
        return _array->back();
    };

    void set(const int index, const_reference val){
        _array->set(index, val);
    };
    void set(const int index, const_pointer val){
        _array->set(index, val);
    };

    void append(const_reference data){
        _array->push_back(&data);
    };
    void append(const_pointer data){
        _array->push_back(data);
    };

    void prepend(const_reference data){
        _array->push_front(&data);
    };
    void prepend(const_pointer data){
        _array->push_front(data);
    };

    void insert_at(const_reference data, const int index){
        _array->insert(&data, index);
    };
    void remove_at(const int index){
        _array->remove(index);
    };

    Sequence* sub_sequence(const int from, const int to) const{
        ArraySequence* result = new ArraySequence();
        *result->_array = _array->subarray(from, to);
        return dynamic_cast<Sequence*>(result);
    };

    void concate(const Sequence* other){
        iterator iter = other->begin();
        iterator last = other->end();
        _resize(size() + other->size());
        iterator input = at(size() - other->size());
        while(iter != last){
            *input = *iter;
            ++input;
            ++iter;
        };
    };
    void concate(const Sequence& other){
        concate(&other);
    };

    Sequence* get_concated(const Sequence* other) const{
        ArraySequence* result = new ArraySequence(this);
        result->concate(other);
        return dynamic_cast<Sequence*>(result);
    };
    Sequence* get_concated(const Sequence& other) const{
        return get_concated(&other);
    };

    Sequence* get_copy() const{
        return dynamic_cast<Sequence*>(new ArraySequence(this));
    };
    Sequence* get_clean_copy(const int size = 0) const{
        if(size > 0)
            return dynamic_cast<Sequence*>(new ArraySequence(size));
        else
            return dynamic_cast<Sequence*>(new ArraySequence());
    };

    void copy(const_pointer data, const int count){
        _resize(size() + count);
        iterator iter = at(size() - count);
        for(int i = 0; i < count; ++i, ++iter)
            *iter = *(data + i);
    };

    reference operator[](const int index){
        return get(index);
    };
    value operator[](const int index) const{
        return get(index);
    };

    operator std::string() const{
        return (std::string)(*_array);
    };

    Sequence* operator=(const ArraySequence* other){
        return (*this = dynamic_cast<Sequence*>(other));
    };
    Sequence& operator=(const ArraySequence& other){
        return (*this = dynamic_cast<const Sequence&>(other));
    };
    Sequence* operator=(const Sequence* other){
        if(other == 0){
            other = dynamic_cast<Sequence*>(new ArraySequence());
            return (*this = other);
        };
        if(this != other){
            if(this != 0)
                clear();
            if(other->size() != 0){
                _array = new Array(other->size());
                iterator input = begin();
                iterator iter = other->begin();
                iterator last = other->end();
                while(iter != last){
                    *input = *iter;
                    ++input;
                    ++iter;
                };
            } else
                _array = new Array();
        };
        return dynamic_cast<Sequence*>(this);
    };
    Sequence& operator=(const Sequence& other){
        operator=(&other);
        return dynamic_cast<Sequence&>(*this);
    };
    Sequence* operator=(const std::initializer_list<value>& list){
        *this = ArraySequence(list);
        return dynamic_cast<Sequence*>(this);
    };

    bool operator==(const Sequence* other) const{
        if(this == &other)
            return true;
        if(size() != other->size())
            return false;
        iterator iter1 = begin();
        iterator iter2 = other->begin();
        iterator last = end();
        while(iter1 != last){
            if(*iter1 != *iter2)
                return false;
            ++iter1;
            ++iter2;
        };
        return true;
    };
    bool operator==(const Sequence& other) const{
        return (*this == &other);
    };
    bool operator!=(const Sequence* other) const{
        return !(*this == other);
    };
    bool operator!=(const Sequence& other) const{
        return !(*this == &other);
    };

    Sequence* operator+(const Sequence* other) const{
        return get_concated(other);
    };
    Sequence& operator+(const Sequence& other) const{
        return get_concated(other);
    };
    Sequence* operator+(const_reference data) const{
        ArraySequence* result = new ArraySequence(this);
        result->append(data);
        return dynamic_cast<Sequence*>(result);
    };

    void operator+=(const Sequence* other){
        concate(other);
    };
    void operator+=(const Sequence& other){
        concate(other);
    };
    void operator+=(const_reference data){
        append(data);
    };

    iterator begin(){
        return _array->begin();
    };
    const_iterator begin() const{
        return cbegin();
    };
    const_iterator cbegin() const{
        return _array->cbegin();
    };

    iterator at(const int index){
        return _array->at(index);
    };
    const_iterator at(const int index) const{
        return cat(index);
    };
    const_iterator cat(const int index) const{
        return _array->cat(index);
    };

    iterator end(){
        return _array->end();
    };
    const_iterator end() const{
        return cend();
    };
    const_iterator cend() const{
        return _array->cend();
    };

    ~ArraySequence(){
        //this->~Sequence();
        delete _array;
    };
};

#endif // ARRAYSEQUENCE_H
