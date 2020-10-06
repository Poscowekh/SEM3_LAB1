#ifndef LIST_ITERATOR_HPP
#define LIST_ITERATOR_HPP
#include "../_libs.hpp"
#include "Node.hpp"

template<typename value>
class ListIterator : public BaseIterator<value>{
private:
    //friend class List;
    using base_iterator = BaseIterator<value>*;
    using reference = value&;
    using const_reference = const value&;
    using pointer = value*;
    using const_pointer = const value*;
    using node = Node<value>*;
    using const_node = const Node<value>*;

    node _node;

    const_pointer cptr() const{
        if(_is_end())
            throw std::runtime_error("\nList iterator exception: dereferencing end iterator");
        return _node->data;
    };

    reference ref(){
        if(_is_end())
            throw std::runtime_error("\nList iterator exception: dereferencing end iterator");
        return *_node->data;
    };
    const_reference cref() const{
        if(_is_end())
            throw std::runtime_error("\nList iterator exception: dereferencing end iterator");
        return *_node->data;
    };

    value val() const{
        if(_is_end())
            throw std::runtime_error("\nList iterator exception: dereferencing end iterator");
        return *_node->data;
    };

    bool _is_end() const{
        if(_node == 0)
            return true;
        return false;
    };

public:
    ListIterator() = delete;
    ListIterator(node other_node) : _node(other_node) {};
    ListIterator(const_node other_node){
        _node = other_node;
    };
    ListIterator(const ListIterator* other) : _node(other->_node) {};
    ListIterator(const ListIterator& other) : _node(other._node) {};

    base_iterator operator++(){
        if(_is_end())
            throw std::runtime_error("\nList iterator exception: incrementing end iterator");
        _node = _node->next;
        return dynamic_cast<base_iterator>(this);
    };
    base_iterator operator++(int){
        if(_is_end())
            throw std::runtime_error("\nList iterator exception: incrementing end iterator");
        base_iterator copy = dynamic_cast<base_iterator>(new ListIterator(this));
        _node = _node->next;
        return copy;
    };

    base_iterator operator--(){
        if(_is_end())
            throw std::runtime_error("\nList iterator exception: decrementing to null-pointing iterator");
        _node = _node->prev;
        return dynamic_cast<base_iterator>(this);
    };
    base_iterator operator--(int){
        if(_is_end())
            throw std::runtime_error("\nList iterator exception: decrementing to null-pointing iterator");
        base_iterator copy = dynamic_cast<base_iterator>(new ListIterator(this));
        _node = _node->prev;
        return copy;
    };

    base_iterator copy() const{
        return dynamic_cast<base_iterator>(new ListIterator(this));
    };

    reference operator*(){
        return ref();
    };
    const_reference operator*() const{
        return cref();
    };

    const_pointer operator->() const{
        return cptr();
    };

    int operator-(const BaseIterator<value>& other) const override{
        if(typeid(*this) != typeid(other))
            throw std::runtime_error("\nIterator exception: evaluating distance between iterators of different types");
        if(_is_end())
            throw std::runtime_error("\nIterator exception: evaluating distance from end iterator");
        ListIterator iter1 = *dynamic_cast<ListIterator*>(other.copy()),
                iter2 = *dynamic_cast<ListIterator*>(other.copy());
        if(iter1._is_end())
            return 0;
        int distance = 0;
        while(!iter1._is_end() || iter1 != *this){
            iter1++;
            distance++;
        };
        if(iter1 != *this){
            distance = 0;
            while(!iter2._is_end() || iter2 != *this){
                iter2--;
                distance++;
            };
        };
        return distance;
    };

    ~ListIterator(){
        _node = 0;
    };
};

#endif // LIST_ITERATOR_HPP
