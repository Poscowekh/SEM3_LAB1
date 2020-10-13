#ifndef TEST_HPP
#define TEST_HPP
#include "TestFunctions.hpp"

namespace Test {
    class Test {
    private:
        int errors;
        int count;
        std::string name;
        TestFunction* functions;

        Test() : errors(0), count(0), name(std::string()), functions(0) {};
        Test(const Test&) = delete;

        void _realloc(const int times = 1){
            TestFunction* tmp = (TestFunction*)malloc((count + times) * sizeof(TestFunction));
            memcpy(tmp, functions, count * sizeof(TestFunction));
            free(functions);
            functions = tmp;
        };

    public:
        Test(const std::string& test_name) : errors(0), count(0), name(test_name), functions(0) {
            name = test_name;
        };
        Test(Test&& other) : errors(0), count(other.count), name(other.name), functions(other.functions) {
            other.functions = 0;
        };

        void add_test(TestFunction* test_func){
            _realloc();
            memcpy(functions + count, test_func, sizeof(TestFunction));
            count++;
        };
        void add_test(TestFunction& test_func){
            add_test(&test_func);
        };
        void add_test(const std::string& _name, TestFunction::func_ptr func_ptr){
            add_test(new TestFunction(_name, func_ptr));
        };

        int run_tests(){
            using std::cout;
            using std::endl;

            errors = 0;
            TestFunction* tmp;
            cout << "   Testing " << name << "..." << endl;
            for(int i = 0; i < count; i++){
                tmp = functions + i;
                std::string error_name = (*tmp)();
                cout << "       " << "Test " << i + 1 << ": " << tmp->get_name() << " - ";
                /*if(error_name != "OK"){
                    errors++;
                    cout << "error while " << error_name << endl;
                }
                else
                    cout << "no errors" << endl;*/
            };
            cout << "   Test finished";
            if(errors > 0)
                cout << " with " << errors << " errors." << endl;
            else
                cout << " succesfully." << endl;
            return errors;
        };

        int operator()(){
            return run_tests();
        };

        const TestFunction& operator[](const int index) const{
            return *(functions + index);
        };

        Test& operator=(const Test& other){
            if(this != 0)
                free(functions);
            name = other.name;
            errors = count = 0;
            _realloc(other.count);
            count = other.count;
            memcpy(functions, other.functions, sizeof(TestFunction) * count);
            return *this;
        };

        ~Test(){
            free(functions);
        };
    };
};

#endif // TEST_HPP
