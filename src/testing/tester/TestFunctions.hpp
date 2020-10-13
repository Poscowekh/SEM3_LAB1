#ifndef TESTFUNCTIONS_HPP
#define TESTFUNCTIONS_HPP
#include <iostream>

namespace Test {
    class TestFunction {
    public:
        using func_ptr = std::string (*)();

    private:
        func_ptr function;
        std::string name;

        TestFunction() = delete;
        TestFunction(const TestFunction&) = delete;
        TestFunction(TestFunction&&) = delete;

    public:
        TestFunction(const std::string& _name, func_ptr _function)
            : name(_name), function(_function) {};

        std::string operator()(){
            return function();
        };
        const std::string& get_name() const{
            return name;
        };

        ~TestFunction(){
            function = 0;
        };
    };
};

#endif // TESTFUNCTIONS_HPP
