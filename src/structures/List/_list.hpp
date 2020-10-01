#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "list_iterator.hpp"

template<typename T> class List{
private:
    using InitializerFunction = T (*)(const int index);
    //using InitializerLambda = [](const int index) -> T;
    using list_iter = ListIterator<T>;
    using c_list_iter = const ListIterator<T>;
    using iterator = BaseIterator<T>*;
    using const_iterator = const BaseIterator<T>*;

    using Node = Node<T>;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using value = T;

    Node* _head;
    Node* _tail;
    int _size;

    Node* _get_node(const int index) const{
        if(index > _size - 1 || index < 0)
            throw std::runtime_error("\nList exception: index out of range");
        if(index > _size / 2)
            return _from__tail(index);
        return _from__head(index);
    };
    Node* _from__head(const int index) const{
        Node* tmp = _head;
        for(int i = 0; i < index; i++)
            tmp = tmp->next;
        return tmp;
    };
    Node* _from__tail(int index) const{
        Node* tmp = _tail;
        for(int i = _size; i > index + 1; i--)
            tmp = tmp->prev;
        return tmp;
    };

    reference _get_data(const int index){
        return *(_get_node(index)->data);
    };
    value _get_data(const int index) const{
        return *(_get_node(index)->data);
    };

public:
    List() : _size(0), _head(0), _tail(0) {};
    List(const List* other) : List() {
        Node* tmp = other->_head;
        while(tmp != 0){
            push_back(tmp->data);
            tmp = tmp->next;
        };
    };
    List(const List& other) : List(&other) {};
    List(List&& other) : _head(other._head), _tail(other._tail), _size(other._size) {
        other._head = other._tail = 0;
    };

    List(const_pointer data, const int count, const int from = 0) : List() {
        if(data != 0)
            for(int i = from; i < count + from; i++)
                push_back(data + i);
    };
    List(const int size, const_reference default_member = T()) : List() {
        for(int i = 0; i < size; i++)
            push_back(&default_member);
    };
    List(const int size, const_pointer default_member) : List(size, *default_member) {};
    List(const int size, InitializerFunction func) : List() {
        for(int i = 0; i < size; i++)
            push_back(func(i));
    };
    List(std::initializer_list<T> list) : List() {
        auto iter = list.begin();
        for(auto i = 0; i < list.size(); i++)
            push_back(iter++);
    };

    void push_front(const_pointer data, const int count = 1){
        for(int i = 0; i < count; i++){
            Node* tmp = new Node(data + i, 0, _head);
            if(_size == 0)
                _tail = tmp;
            else
                _head->prev = tmp;
            _head = tmp;
            _size++;
        };
    };
    void push_front(const_reference data){
        push_front(&data);
    };
    void push_back(const_pointer data, const int count = 1){
        for(int i = 0; i < count; i++){
            Node* tmp = new Node(data + i, _tail, 0);
            /*
             * tmp->data = data;
            tmp->prev = _tail;
            tmp->next = 0;*/
            if(_size == 0)
                _head = tmp;
            else
                _tail->next = tmp;
            _tail = tmp;
            _size++;
        };
    };
    void push_back(const_reference data){
        push_back(&data);
    };

    reference front(){
        return _get_data(0);
    };
    value front() const{
        return _get_data(0);
    };
    reference get(const int index){
        return _get_data(index);
    };
    value get(const int index) const{
        return _get_data(index);
    };
    reference back(){
        return _get_data(_size - 1);
    };
    value back() const{
        return _get_data(_size - 1);
    };

    void set(const int index, const_pointer data){
        memcpy(_get_node(index)->data, data, sizeof(T));
    };
    void set(const int index, const_reference data){
        set(index, &data);
    };

    void expand(const int count){
        for(int i = 0; i < count; i++)
            push_back(T());
    };

    int size() const{
        return _size;
    };
    bool empty() const{
        if(_size > 0)
            return false;
        return true;
    };
    void clear(){
        pop_back(_size);
        _head = _tail = 0;
        _size = 0;
    };
    void print(const int members_in_line = -1, bool show_indexes = false, bool add_ws = true) const
    //prints the list int []-brackets, if show_indexes=true then prints evvery member as index:member
    {
        std::cout << to_string(members_in_line, show_indexes, add_ws);
    };

    value pop_back(const int count = 1){
        value result;
        for(int i = 0; i < count; i++){
            if(i == count - 1)
                result = T(back());
            if(_size > 1){
                _tail->prev->next = 0;
                free(_tail->data);
                _tail = _tail->prev;
            } else {
                free(_tail);
                _head = _tail = 0;
            };
            _size--;
        };
        return result;
    };
    value pop_front(const int count = 1){
        value result;
        for(int i = 0; i < count; i++){
            if(i == count - 1)
                result = T(back());
            if(_size > 1){
                _head->next->prev = 0;
                free(_head->data);
                _head = _head->next;
            } else {
                free(_head);
                _head = _tail = 0;
            };
            _size--;
        };
        return result;
    };

    void insert(const_pointer data, const int index){
        if(index == 0)
            push_front(data);
        else if(index == _size)
            push_back(data);
        else if(index < _size){
            Node* new_node = new Node(data, 0, _get_node(index));
            new_node->prev = new_node->next->prev;
            new_node->next->prev->next = new_node;
            new_node->next->prev = new_node;
            _size++;
        };
    };
    void insert(const_reference data, const int index){
        insert(&data, index);
    };
    void remove(const int index){
        if(index == 0)
            pop_front();
        else if(index == _size - 1)
            pop_back();
        else{
            Node* tmp = _get_node(index);
            tmp->next->prev = tmp->prev;
            tmp->prev->next = tmp->next;
            delete tmp;
            _size--;
        };
    };

    List sublist(const int from, const int to) const{
        List result = List();
        for(int i = from; i <= to; i++)
            result.push_back(get(i));
        return result;
    };

    void concate(const List* other){
        for(int i = 0; i < other->_size; i++)
            push_back(other->get(i));
    };
    void concate(const List& other){
        concate(&other);
    };
    List get_concated(const List* other){
        List result = List(*this);
        result->concate(other);
        return result;
    };
    List get_concated(const List& other){
        return get_concated(&other);
    };

    List get_copy() const{
        return List(this);
    };

    reference operator[](const int index){
        //allows push_back!
        /*if(index == _size)
            push_back(T());*/
        return get(index);
    };
    value operator[](const int index) const{
        return get(index);
    };

    List operator+(const List& other) const{
        List result = List(this);
        if(this == &other){
            List copy = List(this);
            result.concate(&copy);
        } else
            result.concate(&other);
        return result;
    };
    List& operator+=(const List& other){
        if(this != &other)
            concate(&other);
        else{
            List copy = List(this);
            concate(&copy);
        };
        return *this;
    };
    List operator+(const_reference data) const{
        List result = List(*this);
        result.push_back(&data);
        return result;
    };
    List& operator+=(const_reference data){
        push_back(&data);
        return *this;
    };

    List operator++(){
        List result = List(this);
        push_back(T());
        return result;
    };
    List operator++(const int count){
        List result = List(this);
        for(int i = 0; i < count; i++)
            push_back(T());
        return result;
    };

    bool operator==(const List& list) const{
        if(_size == 0 && list._size == 0)
            return true;
        if(_size != list._size)
            return false;
        Node* tmp1 = _head;
        Node* tmp2 = list._head;
        for(int i = 0; i < _size; i++){
            if(*(tmp1->data) != *(tmp2->data))
                return false;
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        };
        return true;
    };
    bool operator!=(const List& list) const{
        return !(*this == list);
    };

    List& operator=(const List& other){
        if(this != &other){
            if(&other == 0)
                *this = List();
            else{
                if(this == 0){
                    _size = 0;
                    _head = _tail = 0;
                } else
                    clear();
                Node* tmp = other._head;
                while(tmp != 0){
                    push_back(tmp->data);
                    tmp = tmp->next;
                };
            };
        };
        return *this;
    };
    List& operator=(std::initializer_list<T> list){
        *this = List(list);
        return *this;
    };

    std::string to_string(const int members_in_line = -1, bool show_indexes = false, bool add_ws = false) const{
        if(members_in_line == -1)
            return to_string(_size, show_indexes, add_ws);
        std::string result = " [ ";
        if(_size == 0)
            return result + ']';
        else {
            for(int i = 0; i < _size - 1; i++){
                std::string tmp;
                if(show_indexes)
                    tmp += std::to_string(i) + ':';
                tmp += std::to_string(get(i)) + ", ";
                result += tmp;
                if(members_in_line != 1){
                    if(i != 0 && i % members_in_line == members_in_line - 1)
                        result += "\n   ";
                } else
                    result += "\n   ";
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
    friend std::ostream& operator<<(std::ostream& out, const List& list){
        out << list.to_string(-1, false, true);
        return out;
    };

    friend List operator+(const_reference value, const List& list){
        List result = List(list);
        result.push_front(value);
        return result;
    };

    /*friend std::istream& operator>>(std::istream& in, List& list){
        list = List();
        int size = 0;
        in >> size;
        for(int i = 0; i < size; i++){
            T tmp = T();
            in >> tmp;
            list.push_back(tmp);
        };
        return in;
    };*/

    int find_index(const_reference data){
        auto tmp = _head;
        int index = 0;
        while(tmp != 0){
            index++;
            if(tmp->_data == data)
                return index;
        };
        return -1;
    };
    bool find(const_reference data){
        if(find_index(data) >= 0)
            return true;
        return false;
    };

    iterator begin(){
        iterator result = dynamic_cast<iterator>(new list_iter(_get_node(0)));
        return result;
    };
    const_iterator begin() const{
        return cbegin();
    };
    const_iterator cbegin() const{
        const_iterator result = dynamic_cast<const_iterator>(new c_list_iter(_get_node(0)));
        return result;
    };

    iterator at(const int index){
        iterator result = dynamic_cast<iterator>(new list_iter(_get_node(index)));
        return result;
    };
    const_iterator at(const int index) const{
        return cat(index);
    };
    const_iterator cat(const int index) const{
        const_iterator result = dynamic_cast<const_iterator>(new c_list_iter(_get_node(index)));
        return result;
    };

    iterator end(){
        _get_node(_size - 1);
        iterator result = dynamic_cast<iterator>(new list_iter(_tail->next));
        return result;
    };
    const_iterator end() const{
        return cend();
    };
    const_iterator cend() const{
        _get_node(_size - 1);
        const_iterator result = dynamic_cast<const_iterator>(new c_list_iter(_tail->next));
        return result;
    };

    ~List(){
        clear();
        //delete end_node;
    };
};

#endif // LINKEDLIST_H
