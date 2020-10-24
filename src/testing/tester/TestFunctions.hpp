#ifndef TESTFUNCTIONS_HPP
#define TESTFUNCTIONS_HPP
#include <iostream>

namespace Testing {
    class TestFunction {
    public:
        using func_ptr = std::string (*)();

    private:
        func_ptr function;
        std::string name;

        TestFunction() = delete;
        TestFunction(const TestFunction&) = delete;

    public:
        TestFunction(const std::string& _name, func_ptr _function)
            : name(_name), function(_function) {};
        TestFunction(TestFunction&& other) : name(other.name), function(other.function) {
            other.function = 0;
        };

        std::string operator()() const{
            return function();
        };
        const std::string& get_name() const{
            return name;
        };

        TestFunction& operator=(const TestFunction&) = delete;
        TestFunction& operator=(TestFunction&& other) {
            function = other.function;
            name = other.name;
            other.function = 0;
            return *this;
        };

        ~TestFunction(){
            function = 0;
        };
    };
};

#endif // TESTFUNCTIONS_HPP
