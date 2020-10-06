#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include "array_iterator.hpp"
#include "../InterfaceIterator.hpp"

template<typename T> class Array{
private:
    using InitializerFunction = T (*)(const int index);
    using arr_iter = ArrayIterator<T>;
    using c_arr_iter = const ArrayIterator<T>;
    using base_iter = BaseIterator<T>*;
    using cbase_iter = const BaseIterator<T>*;
    using iterator = Iterator<T>;
    using const_iterator = const Iterator<T>;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using value = T;
    //using const_value = const T;

    int _size;
    int _elsize;
    int _allocated;
    //int _buffer_size = 0;
    pointer _data;   //storage location

    inline pointer _alloc(const int size) const noexcept{
        return pointer(malloc(_elsize * size));
    };

    void _realloc_back(const int new_alloc){
        //alloc new memory size of new_alloc and realloc existing data
        pointer tmp = _alloc(new_alloc);
        if(new_alloc >= _size)
            memcpy(tmp, _data, _elsize * _size);
        else
            memcpy(tmp, _data, _elsize * new_alloc);
        free(_data);
        _data = tmp;
        _allocated = new_alloc;
    };
    void _dealloc_back(const int dealloc = 1){
        if(_allocated - dealloc < 0)
            throw std::runtime_error("\nArray exception: deallocating non-existent memory");
        pointer tmp = _alloc(_allocated - dealloc);
        if(dealloc < _size){
            memcpy(tmp, _data + dealloc, _elsize * (_size - dealloc));
            _size -= dealloc;
        } else
            _size = 0;
        free(_data);
        _data = tmp;
        _allocated -= dealloc;
    };

    void _realloc_front(const int new_alloc){
        pointer tmp = _alloc(new_alloc);
        memcpy(tmp + new_alloc - _get_buff_size() - _size, _data, _elsize * _size);
        free(_data);
        _data = tmp;
        _allocated = new_alloc;
    };
    void _dealloc_front(const int dealloc = 1){
        if(_allocated - dealloc < 0)
            throw std::runtime_error("\nArray exception: deallocating non-existent memory");
        _size -= dealloc;
        pointer tmp = _alloc(_size + _get_buff_size());
        memcpy(tmp, _data + dealloc, _elsize * _size);
        _allocated -= dealloc;
        free(_data);
        _data = tmp;
    };

    inline int _get_buffer() const noexcept{
        return _allocated - _size;
    };
    int _get_buff_size() const noexcept{
        if(_elsize <= 4)
            return _elsize * 4;
        else if(_elsize <= 8)
            return _elsize;
        else
            return 8;
    };

    void _dealloc_check() noexcept{
        if(_get_buffer() >= 2 * _get_buff_size())
            _dealloc_back(_allocated - _size - _get_buff_size());
    };
    void _realloc_check() noexcept{
        if(_get_buffer() == 0)
            _realloc_back(_size + _get_buff_size());
    };

    pointer _get_ptr(const int index) const{
        if(index < 0 || index > _size - 1)
            throw std::runtime_error("\nArray exception: index out of range");
        return _data + index;
    };

public:
    Array() : _size(0), _allocated(0), _data(0), _elsize(sizeof(T)) {};
    Array(const int size) :
        _elsize(sizeof(T)), _allocated(size + _get_buff_size()), _size(size), _data(pointer(malloc(_size + _get_buff_size()))) {
        if(size < 1)
            throw std::logic_error("\nArray exception: allocation of negative-sized memory");
    };
    Array(const int size, const_reference default_member) : Array(size) {
        iterator iter = begin(), last = end();
        while(iter != last)
            *iter++ = default_member;
    };
    Array(const int size, const_pointer default_member) : Array(size, *default_member) {};
    Array(const_pointer data, const int count) : Array(count) {
        memcpy(_data, data, _elsize * _size);
    };

    Array(const Array* other) : Array(other->_data, other->_size) {};
    Array(const Array& other) : Array(&other) {};
    Array(Array&& other) :
        _elsize(sizeof(T)), _data(other._data), _size(other._size), _allocated(other._allocated) {
        other._data = 0;
    };

    Array(std::initializer_list<T> list) : Array(list.size()) {
        auto iter = list.begin(), end = list.end();
        iterator input = begin();
        while(iter != end)
            *input++ = *iter++;
    };
    Array(InitializerFunction func, const int size) : Array(size) {
        auto iter = begin(), last = end();
        while(iter != last)
            *iter = func(*iter);
    };
    Array(iterator from, iterator to) : Array(to - from) /*rework*/{
        iterator copy = from, iter = begin();
        while(copy != to)
            *iter++ = *copy++;
    };

    int size() const{
        return _size;
    };
    int el_size() const{
        return _elsize;
    };
    void clear(){
        _dealloc_back(_allocated);
        _size = _allocated = 0;
    };
    bool empty() const{
        if(_size > 0)
            return false;
        return true;
    };
    void resize(const int size){
        if(size < 0)
            throw std::logic_error("\nArray exception: allocation of negative-sized memory");
        if(size >= _allocated){
            _realloc_back(size + _get_buff_size());
            _size = size;
        } else
            _size = size;
    };
    void remove_buffer(){
        _realloc_back(_size);
    };
    void buffer_size() const{
        return _get_buffer();
    };
    void print(const int members_in_line = 15, bool show_indexes = false, bool add_ws = true) const{
        std::cout << to_string(members_in_line, show_indexes, add_ws);
    };

    value front() const{
        return *_get_ptr(0);
    };
    reference front(){
        return *_get_ptr(0);
    };
    value get(const int index) const{
        return *_get_ptr(index);
    };
    reference get(const int index){
        return *_get_ptr(index);
    };
    value back() const{
        return *_get_ptr(_size - 1);
    };
    reference back(){
        return *_get_ptr(_size - 1);
    };
    const_pointer get_pointer() const{
        return _data;
    };

    void copy_from_to(const_pointer data, const int count, const int from){
        pointer tmp = _alloc(_size + count + _get_buff_size());
        memcpy(tmp, _data, _elsize * from);
        memcpy(tmp + from, data, _elsize * count);
        memcpy(tmp + from + count, _data + from, _elsize * (_size - from));
        free(_data);
        _data = tmp;
        _size += count;
        _allocated = _size + count + _get_buff_size();
    };

    void set(const int index, const_pointer data, const int from_index = 0){
        memcpy(_data + index, data + from_index, _elsize);
    };
    void set(const int index, const_reference data){
        set(index, &data);
    };

    value pop_back(const int count = 1){
        T result = get(_size - count);
        _size -= count;
        _dealloc_check();
        return result;
    };
    value pop_front(const int count = 1){
        T result = get(count - 1);
        _dealloc_front(count);
        return result;
    };

    void push_back(const_pointer data, const int count){
        //rework is better
        for(int i = 0; i < count; i++)
            push_back(data + i);
    };
    void push_back(const_pointer data){
        _realloc_check();
        memcpy(_data + _size, data, _elsize);
        _size++;
    };
    void push_back(const_reference data){
        push_back(&data);
    };

    void push_front(const_pointer data, const int count = 1){
        _realloc_front(_size + count + _get_buff_size());
        memcpy(_data, data, _elsize * count);
        _size += count;
    };
    void push_front(const_reference data){
        push_front(&data);
    };

    void remove(const_pointer data){
        int index = find(data);
        if(index == -1)
            throw std::runtime_error("\nArray exception: removing non-existent member");
        remove_index(index);
    };
    void remove(const_reference data){
        remove(&data);
    };
    void remove_index(const int index){
        if(index < 0 || index >= _size)
            throw std::runtime_error("\nArray exception: index out of range");
        else if(index == 0)
            pop_front();
        else if(index == _size - 1)
            pop_back();
        else {
            pointer tmp = _alloc(_size - 1 + _get_buff_size());
            memcpy(tmp, _data, _elsize * index);
            memcpy(tmp + index, _data + index + 1, _elsize * (_size - index));
            free(_data);
            _data = tmp;
            _size--;
        };
    };
    void insert(const_pointer data, const int index){
        if(index < 0 || index > _size)
            throw std::runtime_error("\nArray exception: index out of range");
        else if(index == 0)
            push_front(data);
        else if(index == _size)
            push_back(data);
        else {
            pointer tmp = _alloc(_size + 1 + _get_buff_size());
            memcpy(tmp, _data, index * _elsize);
            memcpy(tmp + index, data, _elsize);
            memcpy(tmp + index + 1, _data + index, _elsize * (_size - index));
            free(_data);
            _data = tmp;
            _size++;
        };
    };
    void insert(const_reference data, const int index){
        insert(&data, index);
    };


    void concate(const Array& other){
        concate(&other);
    };
    void concate(const Array* other){
        copy_from_to(other->_data, other->_size, _size);
    };

    Array get_concated(const Array* other){
        Array result = Array(this);
        result.concate(other);
        return result;
    };
    Array get_concated(const Array& other){
        return get_concated(&other);
    };

    Array subarray(const int from, const int to){
        if(from > to)
            return subarray(to, from);
        if(from < 0 || to < 0 || from > _size - 1 || to > _size - 1)
            throw std::runtime_error("\nArray exception: index out of range");
        return Array(_data + from, to - from + 1);
    };

    Array operator+(const Array& other) const{
        Array result = Array(this);
        result.concate(&other);
        return result;
    };
    Array& operator+=(const Array& other){
        concate(&other);
        return *this;
    };

    Array operator+(const_reference data) const{
        Array result = Array(this);
        result.push_back(&data);
        return result;
    };
    Array& operator+=(const_reference data){
        push_back(&data);
        return *this;
    };

    friend Array operator+(const_reference val, const Array& array){
        Array result = Array();
        result.push_back(&val);
        result.concate(&array);
        return result;
    };

    bool operator==(const Array& other) const{
        if(this == &other)
            return true;
        if(_size == 0 && other._size == 0)
            return true;
        if(_size != other._size)
            return false;
        pointer tmp1 = _data;
        pointer tmp2 = other._data;
        for(int i = 0; i < _size; i++){
            tmp1 = tmp1 + i;
            tmp2 = tmp2 + i;
            if(*tmp1 != *tmp2)
                return false;
        };
        return true;
    };
    bool operator==(const Array* other) const{
        return *this == *other;
    };
    bool operator!=(const Array& other) const{
        return !(*this == other);
    };
    bool operator!=(const Array* other) const{
        return !(*this == *other);
    };

    Array& operator=(const Array& other){
        if(this != &other){
            if(&other == 0)
                *this = Array();
            else{
                if(this == 0){
                    _allocated = 0;
                    _elsize = sizeof(T);
                    _size = 0;
                    _data = 0;
                } else
                    clear();
                copy_from_to(other._data, other._size, 0);
            };
        };
        return *this;
    };
    Array* operator=(const Array* other){
        *this = *other;
        return this;
    };
    Array& operator=(std::initializer_list<T> list){
        *this = Array(list);
        return *this;
    };

    reference operator[](const int index){
        return get(index);
    };
    value operator[](const int index) const{
        return get(index);
    };

    std::string to_string(const int members_in_line = 1, bool show_indexes = false, bool add_ws = false) const{
        std::string result = " [ ";
        if(_size == 0)
            return result + ']';
        else {
            for(int i = 0; i < _size - 1; i++){
                std::string tmp;
                if(show_indexes)
                    tmp += std::to_string(i) + ':';
                tmp += std::to_string(get(i)) + ", ";
                if(i != 0 && i % members_in_line == members_in_line - 1)
                    tmp += "\n   ";
                result += tmp;
            };
            if(show_indexes)
                result += std::to_string(_size - 1) + ':';
            result += std::to_string(back()) + " ]";
            if(add_ws)
                result += '\n';
        };
        return result;
    };
    explicit operator std::string() const{
        return to_string(1, true);
    };
    friend std::ostream& operator<<(std::ostream& out, const Array& array){
        out << array.to_string(10, false, true);
        return out;
    };

    iterator begin(){
        return iterator(dynamic_cast<base_iter>(new arr_iter(_data)));
    };
    const_iterator begin() const{
        return cbegin();
    };
    const_iterator cbegin() const{
        return const_iterator(dynamic_cast<cbase_iter>(new c_arr_iter(_data)));
    };

    iterator at(const int index){
        return iterator(dynamic_cast<base_iter>(new arr_iter(_get_ptr(index))));
    };
    const_iterator at(const int index) const{
        return cat(index);
    };
    const_iterator cat(const int index) const{
        return const_iterator(dynamic_cast<cbase_iter>(new c_arr_iter(_get_ptr(index))));
    };

    iterator end(){
        return iterator(dynamic_cast<base_iter>(new arr_iter(_data + _size)));
    };
    const_iterator end() const{
        return cend();
    };
    const_iterator cend() const{
        return const_iterator(dynamic_cast<cbase_iter>(new c_arr_iter(_data + _size)));
    };

    int find_index(const_pointer data) const{
        pointer tmp = _data;
        int index = 0;
        while(tmp != 0){
            index++;
            if(*tmp == *data){
                tmp = 0;
                return index;
            };
            tmp += sizeof(T);
        };
        tmp = 0;
        return -1;
    };
    int find_index(const_reference data) const{
        return find_index(&data);
    };
    bool find(const_pointer data) const{
        if(find_index(data) == -1)
            return false;
        return true;
    };
    bool find(const_reference data) const{
        return find(&data);
    };

    ~Array(){
        free(_data);
    };
};

#endif // DYNAMICARRAY_H
