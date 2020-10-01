#ifndef _LIBS_HPP
#define _LIBS_HPP
#include <memory>
#include <stdexcept>
#include <iostream>
#include "base_iterator.hpp"

//string multiplication
/*std::string operator*(const std::string& string, const int count){
    return std::string(string, count);
};
std::string& operator*=(std::string& string, const int count){
    string = std::string(string, count);
    return string;
};
std::string operator*(const int count, const std::string& string){
    return std::string(string, count);
};
std::string& operator*=(const int count, std::string& string){
    string = std::string(string, count);
    return string;
};
*/

namespace std{
    string to_string(const string& string){
        return string;
    };
};

#endif // _LIBS_HPP
