#ifndef TESTENGINE_HPP
#define TESTENGINE_HPP
#include "Test.hpp"

namespace Testing {
    class Tester {
    private:
        int count = 0;
        Test* tests = 0;

        Tester(const Tester&) = delete;
        Tester& operator=(Tester) = delete;

        void _realloc(const int times = 1){
            Test* tmp = (Test*)malloc((count + times) * sizeof(Test));
            memcpy(tmp, tests, count * sizeof(Test));
            free(tests);
            tests = tmp;
            tmp = 0;
        };
        const Test& _get(const int index) const{
            return (*this)[index];
        };

    public:
        Tester() : count(0), tests(0) {};
        Tester(Tester&& other) : count(other.count), tests(other.tests) {
            other.tests = 0;
        };

        void add_test(const Test* new_test){
            _realloc();
            memcpy(tests + count, new_test, sizeof(Test));
            ++count;
        };
        void add_test(const Test& new_test){
            add_test(&new_test);
        };

        int run_all_tests() const{
            using std::endl;
            using std::cout;
            int errors = 0;

            cout << "RUNNING ALL TESTS" << endl;
            for(int i = 0; i < count; ++i){
                cout << "TEST " << i + 1 << ":" << endl;
                errors += _get(i).run_tests();
            };
            cout << "TESTS FINISHED:  ";
            if(errors > 0)
                cout << errors << " errors found." << endl;
            else
                cout << "SUCCESS." << endl;

            return errors;
        };

        Tester& operator=(Tester&& other){
            //if(this != 0)
            free(tests);
            count = other.count;
            tests = other.tests;
            other.tests = 0;
            return *this;
        };/*
        Tester& operator=(const Tester& other){
            if(this != 0)
                free(tests);
            count = 0;
            _realloc(other.count);
            count = other.count;
            memcpy(tests, other.tests, count * sizeof(Test));
            return *this;
        };*/

        const Test& operator[](const int index) const{
            if(index < 0 || index >= count)
                throw std::runtime_error("Test out of range");
            return *(tests + index);
        };

        int operator()() const{
            return run_all_tests();
        };

        ~Tester(){
            free(tests);
        };
    };
};
#endif // TESTENGINE_HPP
