#ifndef TESTS_SEQUENCE_HPP
#define TESTS_SEQUENCE_HPP
#include "../tester/_assert_functions.hpp"
#include "../../Structures.hpp"

namespace Testing {
    std::string test_sequence_create(){
        std::string result = std::string();
        using Seq = Sequence<int>*;
        using LSeq = ListSequence<int>;
        using ASeq = ArraySequence<int>;
        int size = rand();
        _sample test_data = _sample(size);

        Seq test1a = new LSeq();
        Seq test1b = new ASeq();
        if(!test1a->empty())
            _add_str(result, std::string("empty construction (ListSequence)"));
        if(!test1b->empty())
            _add_str(result, std::string("empty construction (ArraySequence)"));

        test1a = new LSeq(test_data.data, test_data.size);
        if(!_assert_equal(test1a, test_data))
            _add_str(result, std::string("pointer construction (ListSequence)"));
        test1b = new ASeq(test_data.data, test_data.size);
        if(!_assert_equal(test1a, test1b) || !_assert_equal(test1b, test_data))
            _add_str(result, std::string("pointer construction (ArraySequence)"));

        Seq test2a = new LSeq(test1b);
        if(!_assert_equal(test2a, test1b))
            _add_str(result, std::string("copy construction (ListSequence)"));
        Seq test2b = new ASeq(test1a);
        if(!_assert_equal(test2b, test1a))
            _add_str(result, std::string("copy construction (ArraySequence)"));

        test1a = new LSeq(test2b->begin(), test2b->end());
        if(!_assert_equal(test1a, test2b))
            _add_str(result, std::string("range construction (ListSequence)"));
        test1b = new ASeq(test2a->begin(), test2a->end());
        if(!_assert_equal(test1b, test2a))
            _add_str(result, std::string("range construction (ArraySequence)"));

        int r = rand();
        test2a = new LSeq(size, r);
        if(!_assert_equal(size, test2a->size()))
            _add_str(result, std::string("default member construction (ListSequence)"));
        test2b = new ASeq(size, r);
        if(!_assert_equal(size, test2b->size()))
            _add_str(result, std::string("default member construction (ArraySequence)"));
        auto iter1 = test2a->begin(),
             last1 = test2a->end();
        while(iter1 != last1){
            if(*iter1 != r){
                _add_str(result, std::string("default member construction (ListSequence)"));
                break;
            };
            ++iter1;
        };
        iter1 = test2a->begin();
        last1 = test2a->end();
        while(iter1 != last1){
            if(*iter1 != r){
                _add_str(result, std::string("default member construction (ArraySequence)"));
                break;
            };
            ++iter1;
        };

        delete test1a;
        delete test1b;
        delete test2a;
        delete test2b;

        if(result.empty())
            return std::string("OK");
        return result;
    };

    std::string test_sequence_add_remove(){
        std::string result = std::string();
        using Seq = Sequence<int>*;
        using LSeq = ListSequence<int>;
        using ASeq = ArraySequence<int>;
        int size = rand() + 10;
        _sample test_data = _sample(size);
        Seq testa = new LSeq(test_data.data, test_data.size);
        Seq testb = new ASeq(test_data.data, test_data.size);

        int r = rand();
        int index = rand() % (size - 1) + 1;

        testa->append(r);
        testa->prepend(r);
        testa->insert_at(r, index);
        if(!_assert_equal(size + 3, testa->size()) || !_assert_equal(testa->front(), r) ||
                !_assert_equal(testa->back(), r) || !_assert_equal(testa->get(index), r))
            _add_str(result, std::string("adding to sequence (ListSequence)"));

        testb->append(r);
        testb->prepend(r);
        testb->insert_at(r, index);
        if(!_assert_equal(testb->size(), size + 3) || !_assert_equal(testb->front(), r) ||
                !_assert_equal(testb->back(), r) || !_assert_equal(testb->get(index), r) || !_assert_equal(testa, testb))
            _add_str(result, std::string("adding to sequence (ArraySequence)"));

        testa->remove_at(index);
        testa->remove_at(0);
        testa->remove_at(testa->size() - 1);
        if(!_assert_equal(size, testa->size()) || !_assert_equal(testa, test_data))
            _add_str(result, std::string("removing from sequence (ListSequence)"));

        testb->remove_at(index);
        testb->remove_at(0);
        testb->remove_at(testb->size() - 1);
        if(!_assert_equal(size, testb->size()) || !_assert_equal(testb, test_data))
            _add_str(result, std::string("removing from sequence (ArraySequence)"));

        if(result.empty())
            return std::string("OK");
        return result;
    };

    std::string test_sequence_iter(){
        std::string result = std::string();
        using Seq = Sequence<int>*;
        using LSeq = ListSequence<int>;
        using ASeq = ArraySequence<int>;
        int size = rand();
        _sample test = _sample(size);
        Seq testa = new LSeq(test.data, test.size);
        Seq testb = new ASeq(test.data, test.size);

        auto itera = testa->begin();;
        for(int i = 0; i < size; i++, itera++)
            if(*itera != test[i]) {
                _add_str(result, std::string("using sequence iterator (ListSequence)"));
                break;
            };

        auto iterb = testb->begin();
        for(int i = 0; i < size; i++, iterb++)
            if(*iterb != test[i]) {
                _add_str(result, std::string("using sequence iterator (ArraySequence)"));
                break;
            };

        if(result.empty())
            return std::string("OK");
        return result;
    };

    std::string test_sequence_concate(){
        std::string result = std::string();
        using Seq = Sequence<int>*;
        using LSeq = ListSequence<int>;
        using ASeq = ArraySequence<int>;
        int size1 = rand(), size2 = rand();
        _sample data1 = _sample(size1);
        _sample data2 = _sample(size2);
        Seq test1 = new LSeq(data1.data, data1.size);
        Seq test2 = new ASeq(data2.data, data2.size);

        Seq testa = test1->get_concated(test2);
        if(!_assert_equal(testa->size(), size1 + size2))
            _add_str(result, std::string("concating sequences size check (ListSequence)"));
        Seq testb = test2->get_concated(test1);
        if(!_assert_equal(testa->size(), testb->size()))
            _add_str(result, std::string("concating sequences size check (ArraySequence)"));

        auto iter = testa->begin(),
             data_iter = test1->begin();
        for(int i = 0; i < size1; ++i, ++iter, ++ data_iter)
            if(*iter != *data_iter) {
                _add_str(result, std::string("concating sequences member check 1 (ListSequence)"));
                break;
            };
        data_iter = test2->begin();
        for(int i = 0; i < size2; ++i, ++iter, ++ data_iter)
            if(*iter != *data_iter) {
                _add_str(result, std::string("concating sequences member check 2 (ListSequence)"));
                break;
            };

        iter = testb->begin();
        data_iter = test2->begin();
        for(int i = 0; i < size2; ++i, ++iter, ++ data_iter)
            if(*iter != *data_iter) {
                _add_str(result, std::string("concating sequences member check 1 (ArraySequence)"));
                break;
            };
        data_iter = test1->begin();
        for(int i = 0; i < size1; ++i, ++iter, ++ data_iter)
            if(*iter != *data_iter) {
                _add_str(result, std::string("concating sequences member check 2 (ArraySequence)"));
                break;
            };

        if(result.empty())
            return std::string("OK");
        return result;
    };

    std::string test_sequence_subsequence(){
        std::string result = std::string();
        using Seq = Sequence<int>*;
        using LSeq = ListSequence<int>;
        using ASeq = ArraySequence<int>;
        int size = rand() + 10;
        _sample data = _sample(size);
        Seq test1a = new LSeq(data.data, data.size);
        Seq test1b = new ASeq(data.data, data.size);

        int index1 = rand() % (size / 2);
        int index2 = rand() % (size / 2) + size / 2;
        int subsize = index2 - index1 + 1;

        Seq test2a = test1a->sub_sequence(index1, index2);
        if(!_assert_equal(test2a->size(), subsize))
            _add_str(result, std::string("creating subsequence size check (ListSequence)"));
        Seq test2b = test1b->sub_sequence(index1, index2);
        if(!_assert_equal(test2b->size(), subsize))
            _add_str(result, std::string("creating subsequence size check (ArraySequence)"));

        auto iter1 = test1a->at(index1),
             iter2 = test2a->begin();
        for(int i = 0; i < subsize; ++i, ++iter1, ++iter2)
            if(*iter1 != *iter2) {
                _add_str(result, std::string("creating subsequence member check (ListSequence)"));
                break;
            };
        iter1 = test1b->at(index1);
        iter2 = test2b->begin();
        for(int i = 0; i < subsize; ++i, ++iter1, ++iter2)
            if(*iter1 != *iter2){
                _add_str(result, std::string("creating subsequence member check (ArraySequence)"));
                break;
            };

        if(result.empty())
            return std::string("OK");
        return result;
    };
};

#endif // TESTS_SEQUENCE_HPP
