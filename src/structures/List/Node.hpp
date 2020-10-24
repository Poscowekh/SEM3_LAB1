#ifndef NODE_HPP
#define NODE_HPP

template<typename T>
struct Node{
    T* data;
    Node* prev;
    Node* next;

    Node() : data(new T()), prev(0), next(0) {};
    Node(const T* _data, Node* _prev, Node* _next) : data(new T(*_data)), prev(_prev), next(_next) {};
    Node(const T& _data, Node* _prev, Node* _next) : Node(&_data, _prev, _next) {};
    Node(const Node* other) : data(new T(*other->data)), prev(0), next(0) {};
    Node(const Node& other) : Node(&other) {};
    //Node(Node&& other) : data(other.data), prev(other.prev), next(other.next) {};

    Node* operator++() const{
        return next;
    };
    Node* operator--() const{
        return prev;
    };

    Node& operator=(const Node& other){
        if(this != &other)
            *this = Node(&other);
        return *this;
    };/*
    Node& operator=(Node&& other){
        if(&other != 0) {
            data = other.data;
            prev = other.prev;
            next = other.next;
        };
        prev = next = 0;
        return *this;
    };*/

    ~Node(){
        delete data;
        prev = next = 0;
    };
};

#endif // NODE_HPP
