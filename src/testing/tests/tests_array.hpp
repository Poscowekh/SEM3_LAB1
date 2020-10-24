#ifndef TESTS_ARRAY_HPP
#define TESTS_ARRAY_HPP
#include "../tester/_assert_functions.hpp"
#include "../../structures/Array/_array.hpp"

namespace Testing {
    std::string test_array_create(){
        std::string result = std::string();
        using Arr = Array<int>;
        int size = rand();
        _sample test_data = _sample(size);

        Arr test1 = Arr();
        if(!test1.empty())
            _add_str(result, std::string("empty construction"));

        test1 = Arr(test_data.data, test_data.size);
        Arr test2 = Arr(test1);
        Arr test3 = Arr(&test1);
        Arr test4 = Arr(test1.begin(), test1.end());
        if(!_assert_equal(test1, test2) || !_assert_equal(test1, test3) || !_assert_equal(test1, test4))
            _add_str(result, std::string("copy construction"));

        int r = rand();
        test2 = Arr(size, r);
        if(!_assert_equal(size, test2.size()) || !_assert_equal_members(test2, r))
            _add_str(result, std::string("default member construction"));

        if(result.empty())
            return std::string("OK");
        return result;
    };

    std::string test_array_add_remove(){
        std::string result = std::string();
        using Arr = Array<int>;
        int size = rand() + 10;
        _sample test_data = _sample(size);
        Arr test = Arr(test_data.data, test_data.size);

        int r = rand();
        test.push_back(r);
        test.push_front(r);
        int index = rand() % (test.size() - 2) + 1;
        test.insert(r, index);
        if(!_assert_equal(size + 3, test.size()) || !_assert_equal(test.front(), r) ||
                !_assert_equal(test.back(), r) || !_assert_equal(test[index], r))
            _add_str(result, std::string("adding to array"));

        test.remove(index);
        test.pop_back();
        test.pop_front();
        if(!_assert_equal(size, test.size()) || !_assert_equal(test, test_data))
            _add_str(result, std::string("removing from array"));

        if(result.empty())
            return std::string("OK");
        return result;
    };

    std::string test_array_iter(){
        std::string result = std::string();
        using Arr = Array<int>;
        int size = rand();
        _sample test_data = _sample(size);
        Arr test = Arr(test_data.data, test_data.size);

        auto iter = test.begin();
        for(int i = 0; i < test.size(); i++, iter++)
            if(*iter != test[i]) {
                _add_str(result, std::string("using array iterator"));
                break;
            };

        if(result.empty())
            return std::string("OK");
        return result;
    };

    std::string test_array_concate(){
        std::string result = std::string();
        using Arr = Array<int>;
        int size1 = rand(), size2 = rand();
        _sample data1 = _sample(size1);
        _sample data2 = _sample(size2);
        Arr test1 = Arr(data1.data, data1.size);
        Arr test2 = Arr(data2.data, data2.size);

        Arr test = test1.get_concated(test2);
        if(!_assert_equal(test.size(), size1 + size2))
            _add_str(result, std::string("concating arrays (size check)"));

        for(int i = 0; i < size1; i++)
            if(test[i] != test1[i]) {
                _add_str(result, std::string("concating arrays (member check 1)"));
                break;
            };

        for(int i = 0; i < size2; i++)
            if(test[i + size1] != test2[i]) {
                _add_str(result, std::string("concating arrays (member check 1)"));
                break;
            };

        if(result.empty())
            return std::string("OK");
        return result;
    };

    std::string test_array_subarray(){
        std::string result = std::string();
        using Arr = Array<int>;
        int size = rand() + 10;
        _sample data = _sample(size);
        Arr test = Arr(data.data, data.size);

        int index1 = rand() % (size / 2);
        int index2 = rand() % (size / 2) + size / 2;

        Arr test2 = test.subarray(index1, index2);
        if(!_assert_equal(test2.size(), index2 - index1 + 1))
            _add_str(result,std::string("creating subarray (size check)"));

        for(int i = 0; i < test2.size(); i++)
            if(test[i + index1] != test2[i]) {
                _add_str(result,std::string("creating subarray"));
                break;
            };

        if(result.empty())
            return std::string("OK");
        return result;
    };
};

#endif // TESTS_ARRAY_HPP
