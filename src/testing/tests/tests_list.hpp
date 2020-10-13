#ifndef TESTS_LIST_HPP
#define TESTS_LIST_HPP
#include "../tester/_assert_functions.hpp"
#include "../../structures/List/_list.hpp"

namespace Test {
    std::string test_list_create(){
        using List = List<int>;
        int size = rand();
        _sample test_data = _sample(size);

        List test1 = List();
        if(!test1.empty())
            return std::string("empty construction");

        test1 = List(test_data.data, test_data.size);
        List test2 = List(test1);
        List test3 = List(&test1);
        List test4 = List(test1.begin(), test1.end());
        if(!_assert_equal(test1, test2) || !_assert_equal(test1, test3) ||_assert_equal(test1, test4))
            return std::string("copy construction");

        int r = rand();
        test2 = List(size, r);
        if(!_assert_equal(size, test2.size()) || !_assert_equal_members(test2, r))
            return std::string("default member construction");

        return std::string("OK");
    };

    std::string test_list_add_remove(){
        using List = List<int>;
        int size = rand() + 10;
        _sample test_data = _sample(size);
        List test = List(test_data.data, test_data.size);

        int r = rand();
        test.push_back(r);
        test.push_front(r);
        int index = rand() % (test.size() - 1) + 1;
        test.insert(r, index);
        if(!_assert_equal(size, test.size() + 3) || !_assert_equal(test.front(), r) || !_assert_equal(test.back(), r) ||
                !_assert_equal(test[index], r))
            return std::string("adding to list");

        test.remove(index);
        test.pop_back();
        test.pop_front();
        if(!_assert_equal(size, test.size()) || !_assert_equal(test, test_data))
            return std::string("removing from list");

        return std::string("OK");
    };

    std::string test_list_iter(){
        using List = List<int>;
        int size = rand();
        _sample test_data = _sample(size);
        List test = List(test_data.data, test_data.size);

        auto iter = test.begin();
        for(int i = 0; i < test.size(); i++, iter++)
            if(*iter != test[i])
                return std::string("using list iterator");

        return std::string("OK");
    };

    std::string test_list_concate(){
        using List = List<int>;
        int size1 = rand(), size2 = rand();
        _sample data1 = _sample(size1);
        _sample data2 = _sample(size2);
        List test1 = List(data1.data, data1.size);
        List test2 = List(data2.data, data2.size);

        List test = test1.get_concated(test2);
        if(!_assert_equal(test.size(), size1 + size2))
            return std::string("concating lists");

        for(int i = 0; i < size1; i++)
            if(test[i] != test1[i])
                return std::string("concating lists");

        for(int i = 0; i < size2; i++)
            if(test[i + size1] != test2[i])
                return std::string("concating lists");

        return std::string("OK");
    };

    std::string test_list_sublist(){
        using List = List<int>;
        int size = rand() + 10;
        _sample data = _sample(size);
        List test = List(data.data, data.size);

        int index1 = rand() % (size / 2);
        int index2 = rand() % (size / 2) + size / 2;

        List test2 = test.sublist(index1, index2);
        if(!_assert_equal(test2.size(), index2 - index1 + 1))
            std::string("creating subarray");

        for(int i = 0; i < test2.size(); i++)
            if(test[i + index1] != test2[i])
                std::string("creating subarray");

        return std::string("OK");
    };
};

#endif // TESTS_LIST_HPP
