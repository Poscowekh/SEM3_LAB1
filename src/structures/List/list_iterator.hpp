#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP
#include "../_libs.hpp"
#include "Node.hpp"

template<typename T>
class ListIterator : public BaseIterator<T>{
private:
    //friend class List;
    using BaseIter = BaseIterator<T>;
    using reference = T&;
    using pointer = T*;

    Node<T>* _node;

    T* ptr(){
        return _node->data;
    };
    T* ptr() const{
        return _node->data;
    };

    T& data(){
        return *_node->data;
    };
    T& data() const{
        return *_node->data;
    };

    T val(){
        return *_node->data;
    };
    T val() const{
        return *_node->data;
    };

    bool _is_end() const{
        if(_node == 0)
            return true;
        return false;
    };

public:
    ListIterator() = delete;
    ListIterator(Node<T>* node) : _node(node) {};
    ListIterator(const Node<T>* node) : _node(node) {};
    ListIterator(const ListIterator* other) : _node(other->_node) {};
    ListIterator(const ListIterator& other) : _node(other._node) {};

    void operator++(){
        _node = _node->next;
    };
    void operator++(int){
        _node = _node->next;
    };

    void operator--(){
        _node = _node->prev;
    };
    void operator--(int){
        _node = _node->prev;
    };

    reference operator*(){
        return *_node->data;
    };
    reference operator*() const{
        return *_node->data;
    };

    pointer operator->(){
        return _node->data;
    };
    const pointer operator->() const{
        return _node->data;
    };

    /*bool operator==(const ListIterator* other) const{
        if(_node == other->_node)
            return true;
        return false;
    };
    bool operator==(const ListIterator& other) const{
        if(_node == other._node)
            return true;
        return false;
    };*/

    ~ListIterator(){
        _node = 0;
    };
};

#endif // LIST_ITERATOR_HPP
