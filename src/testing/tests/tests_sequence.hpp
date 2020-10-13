#ifndef TESTS_SEQUENCE_HPP
#define TESTS_SEQUENCE_HPP
#include "../tester/_assert_functions.hpp"
#include "../../Structures.hpp"

namespace Test {
    std::string test_sequence_create(){
        using Seq = Sequence<int>*;
        using LSeq = ListSequence<int>;
        using ASeq = ArraySequence<int>;
        int size = rand();
        _sample test_data = _sample(size);

        Seq test1a = new LSeq();
        Seq test1b = new ASeq();
        if(!test1a->empty())
            return std::string("empty construction");
        if(!test1b->empty())
            return std::string("empty construction");

        test1a = new LSeq(test_data.data, test_data.size);
        test1b = new LSeq(test_data.data, test_data.size);
        Seq test2a = new LSeq(test1a);
        Seq test2b = new ASeq(test1b);
        if(!_assert_equal(test1a, test1b) || !_assert_equal(test1a, test_data) ||_assert_equal(test2a, test1a) ||
                !_assert_equal(test1a, test2b))
            return std::string("copy construction");

        test1a = new ASeq(*test2a);
        test1b = new LSeq(*test2b);
        test2a = new LSeq(test2b->begin(), test2b->end());
        if(!_assert_equal(test1a, test2a) || !_assert_equal(test1b, test2a) ||_assert_equal(test2a, test2b))
            return std::string("copy construction");

        int r = rand();
        test1a = new LSeq(size, r);
        test1b = new LSeq(size, r);
        if(!_assert_equal(size, test1a->size()) || !_assert_equal(size, test1b->size()) || !_assert_equal_members(test1b, r) ||
                !_assert_equal(test1a, r))
            return std::string("default member construction");

        return std::string("OK");
    };

    std::string test_sequence_add_remove(){
        using Seq = Sequence<int>*;
        using LSeq = ListSequence<int>;
        using ASeq = ArraySequence<int>;
        int size = rand() + 10;
        _sample test_data = _sample(size);
        Seq testa = new LSeq(test_data.data, test_data.size);
        Seq testb = new LSeq(test_data.data, test_data.size);

        int r = rand();
        testa->append(r);
        testb->append(r);
        testa->prepend(r);
        testb->prepend(r);
        int index = rand() % (size - 1) + 1;
        testa->insert_at(r, index);
        testb->insert_at(r, index);
        if(!_assert_equal(size, testa->size() + 3) || !_assert_equal(size, testb->size() + 3) || !_assert_equal(testa->front(), r) ||
                !_assert_equal(testb->front(), r) || !_assert_equal(testa->back(), r) || !_assert_equal(testb->back(), r) ||
                !_assert_equal(testa->get(index), r) || !_assert_equal(testb->get(index), r) || !_assert_equal(testa, testb))
            return std::string("adding to sequence");

        testa->remove_at(index);
        testb->remove_at(index);
        testa->remove_at(0);
        testb->remove_at(0);
        testa->remove_at(testa->size() - 1);
        testb->remove_at(testb->size() - 1);
        if(!_assert_equal(size, testa->size()) || !_assert_equal(testa, test_data) || !_assert_equal(testa, testb))
            return std::string("removing from sequence");

        return std::string("OK");
    };

    std::string test_sequence_iter(){
        using Seq = Sequence<int>*;
        using LSeq = ListSequence<int>;
        using ASeq = ArraySequence<int>;
        int size = rand();
        _sample test = _sample(size);
        Seq testa = new LSeq(test.data, test.size);
        Seq testb = new ASeq(test.data, test.size);

        auto itera = testa->begin();
        auto iterb = testb->begin();
        for(int i = 0; i < size; i++, itera++, iterb++)
            if(*itera != test[i] || *iterb != test[i])
                return std::string("using sequence iterator");

        return std::string("OK");
    };

    std::string test_sequence_concate(){
        using Seq = Sequence<int>*;
        using LSeq = ListSequence<int>;
        using ASeq = ArraySequence<int>;
        int size1 = rand(), size2 = rand();
        _sample data1 = _sample(size1);
        _sample data2 = _sample(size2);
        Seq test1 = new LSeq(data1.data, data1.size);
        Seq test2 = new ASeq(data2.data, data2.size);

        Seq testa = test1->get_concated(test2);
        Seq testb = test2->get_concated(test1);
        if(!_assert_equal(testa, testb) || !_assert_equal(testa->size(), testb->size()) ||
                !_assert_equal(testa->size(), size1 + size2))
            return std::string("concating sequences");

        for(int i = 0; i < size1; i++)
            if(testa->get(i) != test1->get(i))
                return std::string("concating sequences");
        for(int i = 0; i < size2; i++)
            if(testb->get(i) != test2->get(i))
                return std::string("concating sequences");

        for(int i = 0; i < size2; i++)
            if(testa->get(i + size1) != test2->get(i))
                return std::string("concating sequences");
        for(int i = 0; i < size1; i++)
            if(testb->get(i + size2) != test1->get(i))
                return std::string("concating sequences");

        return std::string("OK");
    };

    std::string test_sequence_subsequence(){
        using Seq = Sequence<int>*;
        using LSeq = ListSequence<int>;
        using ASeq = ArraySequence<int>;
        int size = rand() + 10;
        _sample data = _sample(size);
        Seq test1a = new LSeq(data.data, data.size);
        Seq test1b = new ASeq(data.data, data.size);

        int index1 = rand() % (size / 2);
        int index2 = rand() % (size / 2) + size / 2;

        Seq test2a = test1a->sub_sequence(index1, index2);
        Seq test2b = test1b->sub_sequence(index1, index2);
        if(!_assert_equal(test2a->size(), index2 - index1 + 1) || !_assert_equal(test2b->size(), test2b->size()))
            std::string("creating subsequence");

        for(int i = 0; i < test2a->size(); i++)
            if(test1a->get(i + index1) != test2a->get(i))
                std::string("creating subsequence");
        for(int i = 0; i < test2b->size(); i++)
            if(test1b->get(i + index1) != test2b->get(i))
                std::string("creating subsequence");

        return std::string("OK");
    };
};

#endif // TESTS_SEQUENCE_HPP
