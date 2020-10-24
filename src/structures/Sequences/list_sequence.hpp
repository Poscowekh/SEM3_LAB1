#ifndef _LSEQ_HPP
#define _LSEQ_HPP
#include "_sequence.hpp"

template<typename T> class ListSequence : public Sequence<T>{
private:
    using InitializerFunction = T (&)(const int index);
    using Sequence = Sequence<T>;
    using Array = Array<T>;
    using List = List<T>;
    using iterator = Iterator<T>;
    using const_iterator = const Iterator<T>;

    using value = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;

    List* _list;

public:
    ListSequence() : _list(new List()) {};
    ListSequence(const ListSequence* other) : _list(new List(other->_list)) {};
    ListSequence(const ListSequence& other) : ListSequence(&other) {};
    ListSequence(ListSequence&& other) : _list(new List(other._list)){
        other._list = 0;
    };

    ListSequence(const Sequence* other) : ListSequence(other->begin(), other->end()) {};
    ListSequence(const Sequence& other) : ListSequence(&other) {};
    ListSequence(Sequence&& other) : ListSequence(&other) {
        other._list = 0;
    };

    ListSequence(const List* list) : _list(new List(list)) {};
    ListSequence(const List& list) : ListSequence(&list) {};
    ListSequence(List&& list) : _list(new List(list)) {};

    ListSequence(const Array* array) : ListSequence(array->begin(), array->end()) {};
    ListSequence(const Array& array) : ListSequence(&array) {};
    ListSequence(Array&& array) : ListSequence(&array) {
        &array = 0;
    };

    ListSequence(const_pointer data, const int count) : _list(new List(data, count)) {};
    ListSequence(const int size, InitializerFunction func) : _list(new List(size, func)) {};
    ListSequence(std::initializer_list<T> list) : _list(new List(list)) {};
    ListSequence(const int size, const_reference default_value = T()) : _list(new List(size, default_value)) {};
    ListSequence(const int size, const_pointer default_value) : ListSequence(size, *default_value) {};
    ListSequence(iterator from, iterator to) : _list(new List(from, to)) {};

    int size() const{
        return _list->size();
    };
    void clear(){
        if(this != 0)
            _list->clear();
    };
    bool empty() const{
        return _list->empty();
    };
    void print(const int members_in_line = 1, bool show_indexes = false, bool add_ws = true) const{
        _list->print(members_in_line, show_indexes, add_ws);
    };

    iterator begin(){
        return _list->begin();
    };
    const_iterator begin() const{
        return _list->cbegin();
    };
    const_iterator cbegin() const{
        return _list->cbegin();
    };
    iterator at(const int index){
        return _list->at(index);
    };
    const_iterator at(const int index) const{
        return _list->cat(index);
    };
    const_iterator cat(const int index) const{
        return _list->cat(index);
    };
    iterator end(){
        return _list->end();
    };
    const_iterator end() const{
        return _list->cend();
    };
    const_iterator cend() const{
        return _list->cend();
    };

    reference front(){
        return _list->front();
    };
    value front() const{
        return _list->front();
    };
    reference get(const int index){
        return _list->get(index);
    };
    value get(const int index) const{
        return _list->get(index);
    };
    reference back(){
        return _list->back();
    };
    value back() const{
        return _list->back();
    };

    void set(const int index, const_reference data){
        _list->set(index, &data);
    };
    void set(const int index, const_pointer data){
        _list->set(index, data);
    };

    void append(const_reference data){
        _list->push_back(&data);
    };
    void append(const_pointer data){
        _list->push_back(data);
    };
    void prepend(const_reference data){
        _list->push_front(&data);
    };
    void prepend(const_pointer data){
        _list->push_front(data);
    };

    void insert_at(const_reference data, const int index){
        _list->insert(&data, index);
    };
    void insert_at(const_pointer data, const int index){
        _list->insert(data, index);
    };
    void remove_at(const int index){
        _list->remove(index);
    };

    Sequence* sub_sequence(const int from, const int to) const{
        return dynamic_cast<Sequence*>(new ListSequence(_list->sublist(from, to)));
    };

    void copy(const_pointer data, const int count){
        _list->push_back(data, count);
    };

    void concate(const Sequence* other){
        auto iter = other->begin(),
             last = other->end();
        while(iter != last) {
            _list->push_back(*iter);
            ++iter;
        };
    };
    void concate(const Sequence& other){
        concate(&other);
    };
    Sequence* get_concated(const Sequence* other) const{
        ListSequence* result = new ListSequence(this);
        result->concate(other);
        return dynamic_cast<Sequence*>(result);
    };
    Sequence* get_concated(const Sequence& other) const{
        return get_concated(&other);
    };

    Sequence* get_copy() const{
        return dynamic_cast<Sequence*>(new ListSequence(this));
    };
    Sequence* get_clean_copy(const int size = 1) const{
        if(size > 0)
            return dynamic_cast<Sequence*>(new ListSequence(size));
        else
            return dynamic_cast<Sequence*>(new ListSequence());
    };

    Sequence& copy_to(Sequence& destination, const int from, const int to) const{
        _list->copy_to(destination._list, from, to);
        return destination;
    };

    Sequence* operator+(const ListSequence* other) const{
        Sequence* result = new ListSequence(this);
        result->concate(other);
        return result;
    };
    Sequence* operator+(const ListSequence& other) const{
        Sequence* result = new ListSequence(this);
        result->concate(&other);
        return result;
    };
    Sequence& operator+=(const ListSequence* other){
        concate(other);
        return *this;
    };
    Sequence& operator+=(const ListSequence& other){
        concate(&other);
        return *this;
    };

    Sequence* operator+(const_reference data) const{
        auto result = new ListSequence(this);
        result->append(&data);
        return result;
    };
    Sequence& operator+=(const_reference data){
        append(&data);
        return *this;
    };

    reference operator[](const int index){
        return _list->get(index);
    };
    value operator[](const int index) const{
        return _list->get(index);
    };

    operator std::string() const{
        return (std::string)(*_list);
    };
    /*friend std::ostream& operator<<(std::ostream& out, const ListSequence& seq){
        out << (*seq._list);
        return out;
    };*/

    Sequence* operator=(const ListSequence* other){
        return (*this = dynamic_cast<const Sequence*>(other));
    };
    Sequence& operator=(const ListSequence& other){
        return (*this = dynamic_cast<const Sequence&>(other));
    };
    Sequence* operator=(const Sequence* other){
        if(this != other){
            if(this != 0)
                clear();
            auto from = other->begin();
            auto to = other->end();
            while(from != to){
                append(*from);
                ++from;
            };
        };
        return dynamic_cast<Sequence*>(this);
    };
    Sequence& operator=(const Sequence& other){
        operator=(&other);
        return dynamic_cast<Sequence&>(*this);
    };
    Sequence* operator=(const std::initializer_list<T>& list){
        _list = new List(list);
        return dynamic_cast<Sequence*>(this);
    };

    ~ListSequence(){
        //this->~Sequence();
        delete _list;
    };
};

#endif // _LSEQ_HPP
