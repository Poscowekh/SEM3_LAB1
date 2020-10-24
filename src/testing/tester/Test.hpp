 #ifndef TEST_HPP
#define TEST_HPP
#include "TestFunctions.hpp"

namespace Testing {
    template<typename Container>
    class BigTest {
        private:
            std::string name;
            TestFunction* functions = 0;
            Container* dummy = 0;
            int errors = 0;
            int count = 0;

            void _realloc(const int times = 1){
                TestFunction* tmp = reinterpret_cast<TestFunction*>(malloc((count + times) * sizeof(TestFunction)));
                memcpy(tmp, functions, count * sizeof(TestFunction));
                free(functions);
                functions = tmp;
                tmp = 0;
            };

            BigTest() = delete;
            BigTest(const Container&) = delete;

        public:
            BigTest(const std::string& _name, const Container* container) : name(_name), dummy(container) {};
            BigTest(const std::string& _name, const Container& container) : BigTest(_name, &container) {};
            BigTest(Container&& other) : name(other.name), functions(other.functions), count(other.count), dummy(other.dummy) {};

            void add_test(const TestFunction* func){
                _realloc();
                memcpy(functions + count, func, sizeof(TestFunction));
                count++;
            };
            void add_test(const TestFunction& func){
                add_test(&func);
            };
            void add_test(const std::string& _name, TestFunction::func_ptr func){
                add_test(TestFunction(_name, func));
            };

            int run(){
                using std::cout;
                using std::endl;

                errors = 0;
                TestFunction* tmp = 0;

                cout << "   Testing " << name << "..." << endl;
                for(int i = 0; i < count; i++){
                    tmp = functions + i;
                    std::string error_name = (*tmp)();
                    cout << "       " << "Test " << i + 1 << ": " << tmp->get_name() << " == ";
                    if(error_name != "OK"){
                        errors++;
                        cout << "ERROR (while " << error_name << ")\n";
                    }
                    else
                        cout << "success" << endl;
                };
                cout << "   Test finished";
                if(errors > 0)
                    cout << " with " << errors << " errors." << endl;
                else
                    cout << " succesfully." << endl;

                return errors;
            };

            int operator()(){
                return run();
            };

            ~BigTest(){
                functions = 0;
            };
    };

    class Test {
    private:
        int count = 0;
        std::string name = std::string();
        TestFunction* functions = 0;

        Test() = delete;
        Test(const Test&) = delete;

        void _realloc(const int times = 1){
            TestFunction* tmp = (TestFunction*)malloc((count + times) * sizeof(TestFunction));
            memcpy(tmp, functions, count * sizeof(TestFunction));
            free(functions);
            functions = tmp;
            tmp = 0;
        };

    public:
        Test(const std::string& test_name) : name(test_name), functions(0) {
            name = test_name;
        };
        Test(Test&& other) : count(other.count), name(other.name), functions(other.functions) {
            other.functions = 0;
        };

        void add_test(const TestFunction* test_func){
            _realloc();
            memcpy(functions + count, test_func, sizeof(TestFunction));
            ++count;
        };
        void add_test(const TestFunction& test_func){
            add_test(&test_func);
        };
        void add_test(const std::string& _name, TestFunction::func_ptr func_ptr){
            add_test(new TestFunction(_name, func_ptr));
        };

        /*
        int run(){
            using std::cout;
            using std::endl;

            TestFunction* tmp = 0;
        }*/

        int run_tests() const{
            using std::cout;
            using std::endl;

            int errors = 0;
            cout << "   Testing " << name << "..." << endl;
            for(int i = 0; i < count; ++i){
                std::string error_name = (*this)[i]();
                cout << "       " << "Test " << i + 1 << ": " << (*this)[i].get_name() << " == ";
                if(error_name != "OK"){
                    ++errors;
                    cout << "ERROR (while " << error_name << ")\n";
                }
                else
                    cout << "success" << endl;
            };
            cout << "   Test finished";
            if(errors > 0)
                cout << " with " << errors << " errors." << endl;
            else
                cout << " succesfully." << endl;
            return errors;
        };

        int operator()() const {
            return run_tests();
        };

        const TestFunction& operator[](const int index) const{
            return *(functions + index);
        };

        /*
        Test& operator=(const Test& other){
            if(&other != 0){
                if(this != 0)
                    free(functions);
                name = other.name;
                count = 0;
                _realloc(other.count);
                count = other.count;
                memcpy(functions, other.functions, sizeof(TestFunction) * count);
            };
            return *this;
        };*/
        Test& operator=(Test&& other){
            //if(this != 0)
            free(functions);
            name = other.name;
            count = other.count;
            functions = other.functions;
            other.functions = 0;
            return *this;
        };

        ~Test(){
            free(functions);
        };
    };
};

#endif // TEST_HPP
