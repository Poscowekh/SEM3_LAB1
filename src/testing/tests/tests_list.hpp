#ifndef TESTS_LIST_HPP
#define TESTS_LIST_HPP
#include "../tester/_assert_functions.hpp"
#include "../../structures/List/_list.hpp"

namespace Testing {
    std::string test_list_create(){
        std::string result = std::string();
        using List = List<int>;
        int size = rand();
        _sample test_data = _sample(size);

        List test1 = List();
        if(!test1.empty())
            _add_str(result, std::string("empty construction"));

        test1 = List(test_data.data, test_data.size);
        List test2 = List(test1);
        List test3 = List(&test1);
        List test4 = List(test1.begin(), test1.end());
        if(!_assert_equal(test1, test2) || !_assert_equal(test1, test3) || !_assert_equal(test1, test4))
            _add_str(result, std::string("copy construction"));

        int r = rand();
        test2 = List(size, r);
        if(!_assert_equal(size, test2.size()) || !_assert_equal_members(test2, r))
            _add_str(result, std::string("default member construction"));

        if(result.empty())
            return std::string("OK");
        return result;
    };

    std::string test_list_add_remove(){
        std::string result = std::string();
        using List = List<int>;
        int size = rand() + 10;
        _sample test_data = _sample(size);
        List test = List(test_data.data, test_data.size);

        int r = rand();
        test.push_back(r);
        test.push_front(r);
        int index = rand() % (test.size() - 2) + 1;
        test.insert(r, index);
        if(!_assert_equal(size + 3, test.size()) || !_assert_equal(test.front(), r) || !_assert_equal(test.back(), r) ||
                !_assert_equal(test[index], r))
            _add_str(result, std::string("adding to list"));

        test.remove(index);
        test.pop_back();
        test.pop_front();
        if(!_assert_equal(size, test.size()) || !_assert_equal(test, test_data))
            _add_str(result, std::string("removing from list"));

        if(result.empty())
            return std::string("OK");
        return result;
    };

    std::string test_list_iter(){
        std::string result = std::string();
        using List = List<int>;
        int size = rand();
        _sample test_data = _sample(size);
        List test = List(test_data.data, test_data.size);

        auto iter = test.begin();
        for(int i = 0; i < test.size(); ++i, ++iter)
            if(*iter != test[i]) {
                _add_str(result, std::string("using list iterator"));
                break;
            };

        if(result.empty())
            return std::string("OK");
        return result;
    };

    std::string test_list_concate(){
        std::string result = std::string();
        using List = List<int>;
        int size1 = rand(), size2 = rand();
        _sample data1 = _sample(size1);
        _sample data2 = _sample(size2);
        List test1 = List(data1.data, data1.size);
        List test2 = List(data2.data, data2.size);

        List test = test1.get_concated(test2);
        if(!_assert_equal(test.size(), size1 + size2))
            _add_str(result, std::string("concating lists (size check)"));

        auto iter = test.begin();
        for(int i = 0; i < size1; ++i, ++iter)
            if(*iter != test1[i]) {
                _add_str(result, std::string("concating lists (member check 1)"));
                break;
            };

        //iter = test.at(size1);
        for(int i = 0; i < size2; ++i, ++iter)
            if(*iter != test2[i]) {
                _add_str(result, std::string("concating lists (member check 2)"));
                break;
            };

        if(result.empty())
            return std::string("OK");
        return result;
    };

    std::string test_list_sublist(){
        std::string result = std::string();
        using List = List<int>;
        int size = rand() + 10;
        _sample data = _sample(size);
        List test = List(data.data, data.size);

        int index1 = rand() % (size / 2);
        int index2 = rand() % (size / 2) + size / 2;
        int subsize = index2 - index1 + 1;

        List sublist = test.sublist(index1, index2);
        if(!_assert_equal(sublist.size(), subsize))
            _add_str(result, std::string("creating subarray (size check)"));

        auto iter = test.at(index1),
             subiter = sublist.begin();
        for(int i = 0; i < subsize; ++i, ++iter, ++subiter)
            if(*iter != *subiter) {
                _add_str(result, std::string("creating subarray (member check)"));
                break;
            };

        if(result.empty())
            return std::string("OK");
        return result;
    };
};

#endif // TESTS_LIST_HPP
