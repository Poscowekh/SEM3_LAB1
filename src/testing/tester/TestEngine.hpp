#ifndef TESTENGINE_HPP
#define TESTENGINE_HPP
#include "Test.hpp"

namespace Test {
    class Tester {
    private:
        int errors;
        int count;
        Test* tests;

        Tester(const Tester&) = delete;

        void _realloc(const int times = 1){
            Test* tmp = (Test*)malloc((count + times) * sizeof(Test));
            memcpy(tmp, tests, count * sizeof(Test));
            free(tests);
            tests = tmp;
        };

    public:
        Tester() : errors(0), count(0), tests(0) {};
        Tester(Tester&& other) : errors(0), count(other.count), tests(other.tests) {
            other.tests = 0;
        };

        void add_test(const Test* new_test){
            _realloc();
            memcpy(tests + count, new_test, sizeof(Test));
            count++;
        };
        void add_test(const Test& new_test){
            add_test(&new_test);
        };

        void run_tests(){
            using std::endl;
            using std::cout;

            cout << "RUNNING ALL TESTS" << endl;
            for(int i = 0; i < count; i++){
                cout << "TEST " << i + 1 << ":" << endl;
                errors += (tests + i)->run_tests();
            };
            cout << "TESTS FINISHED:  ";
            if(errors > 0)
                cout << errors << " errors found." << endl;
            else
                cout << "no errors found." << endl;
            errors = 0;
        };

        Tester& operator=(const Tester& other){
            if(this != 0)
                free(tests);
            count = errors = 0;
            _realloc(other.count);
            count = other.count;
            memcpy(tests, other.tests, sizeof(Test) * count);
            return *this;
        };

        ~Tester(){
            free(tests);
        };
    };
};
#endif // TESTENGINE_HPP
