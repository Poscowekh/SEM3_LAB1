#ifndef TESTS_HPP
#define TESTS_HPP
#include "tests_array.hpp"
#include "tests_list.hpp"
#include "tests_sequence.hpp"
#include "../tester/TestEngine.hpp"

namespace Test {
    Test tests_for_array(){
        Test test = Test("Array");
        test.add_test("Array creation", test_array_create);
        test.add_test("Array add/remove/insert/etc", test_array_add_remove);
        test.add_test("ArrayIterator", test_array_iter);
        test.add_test("Array concatenation", test_array_concate);
        test.add_test("Array subarray", test_array_subarray);
        return test;
    };

    Test tests_for_list(){
        Test test = Test("List");
        test.add_test("List creation", test_list_create);
        test.add_test("List add/remove/insert/etc", test_list_add_remove);
        test.add_test("ListIterator", test_list_iter);
        test.add_test("List concatenation", test_list_concate);
        test.add_test("List sublist", test_list_sublist);
        return test;
    };

    Test tests_for_sequence(){
        Test test = Test("Sequence");
        test.add_test("Sequence creation", test_sequence_create);
        //test.add_test("Sequence add/remove/insert/etc", test_sequence_add_remove);
        //test.add_test("SequenceIterator", test_sequence_iter);
        //test.add_test("Sequence concatenation", test_sequence_concate);
        //test.add_test("Sequence subsequence", test_sequence_subsequence);
        return test;
    };

    Tester create_tester(){
        Tester tester;
        //tester.add_test(tests_for_array());
        //tester.add_test(tests_for_list());
        tester.add_test(tests_for_sequence());
        return tester;
    };
};

#endif // TESTS_HPP
