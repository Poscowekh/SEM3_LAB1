#ifndef _ASSERT_FUNCTIONS_HPP
#define _ASSERT_FUNCTIONS_HPP
#include "../../structures/InterfaceIterator.hpp"
#include "sample_struct.hpp"

namespace Testing {
    void _add_str(std::string& string, const std::string& addition) {
        if(string.empty())
            string += addition;
        else
            string += " & " + addition;
    };

    template<typename Container, typename std::enable_if<std::is_pointer<Container>{}, int>::type = 0>
    bool _assert_sorted(const Container container){
        if(container->size() < 2)
            return true;
        auto
            iter1 = container->begin(),
            iter2 = ++(container->begin()),
            end = container->end();
        while(iter2 != end)
            if(*iter2++ < *iter1++)
                return false;
        return true;
    };
    template<typename Container, typename std::enable_if<!std::is_pointer<Container>{}, int>::type = 0>
    bool _assert_sorted(const Container container){
        return _assert_sorted(&container);
    };

    template<typename Container, typename std::enable_if<std::is_pointer<Container>{}, int>::type = 0>
    bool _assert_equal(const Container container, const _sample& test){
        if(container->size() != test.size)
            return false;
        if(container->size() == 0)
            return true;
        auto iter = container->begin();
        for(int i = 0; i < test.size; i++, iter++)
            if(*iter != test[i])
                return false;
        return true;
    };
    template<typename Container, typename std::enable_if<!std::is_pointer<Container>{}, int>::type = 0>
    bool _assert_equal(const Container container, const _sample& test){
        return _assert_equal(&container, test);
    };

    template<typename Container1, typename Container2, typename std::enable_if<std::is_pointer<Container1>{} &&
                                                        std::is_pointer<Container2>{} && !std::is_same<Container2, _sample*>{}, int>::type = 0>
    //for pointers
    bool _assert_equal(const Container1 container1, const Container2 container2){
        if(container1->size() != container2->size())
            return false;
        if(container1->size() == 0)
            return true;
        auto
            iter1 = container1->begin(),
            iter2 = container2->begin(),
            end = container1->end();
        while(iter1 != end)
            if(*iter2++ != *iter1++)
                return false;
        return true;
    };
    template<typename Container1, typename Container2, typename std::enable_if<!std::is_pointer<Container1>{} && !std::is_pointer<Container2>{}
                                                        && !std::is_same<Container2, _sample>{}, int>::type = 0>
    //for non-poiters
    bool _assert_equal(const Container1 container1, const Container2 container2){
        return _assert_equal(&container1, &container2);
    };

    bool _assert_equal(const int& first, const int& second){
        return first == second;
    };

    template<typename Container, typename Value, typename std::enable_if<std::is_pointer<Container>{}, int>::type = 0>
    bool _assert_equal_members(const Container container, Value value){
        auto iter = container->begin(),
             last = container->end();
        while(iter != last)
            if(*iter++ != value)
                return false;
        return true;
    };
    template<typename Container, typename Value, typename std::enable_if<!std::is_pointer<Container>{}, int>::type = 0>
    bool _assert_equal_members(const Container container, Value value){
        return _assert_equal_members(&container, value);
    };
};

#endif // _ASSERT_FUNCTIONS_HPP
