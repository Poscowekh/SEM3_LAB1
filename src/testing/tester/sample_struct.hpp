#ifndef SAMPLE_STRUCT_HPP
#define SAMPLE_STRUCT_HPP
#include <iostream>

namespace Testing {
    template<typename T>
    struct __sample {
        T* data;
        int size;

        __sample(const int _size) : size(_size), data((T*)malloc(sizeof(T) * _size)) {
            for(int i = 0; i < size; ++i){
                T r = T(rand());
                memcpy(data + i, &r, sizeof(T));
            };
        };
        __sample(const int _size, const int seed) : size(_size), data((T*)malloc(sizeof(T) * _size)) {
            srand(seed);
            for(int i = 0; i < size; ++i){
                T r = T(rand());
                memcpy(data + i, &r, sizeof(T));
            };
        };
        explicit __sample(__sample&& other) : size(other.size), data(other.data) {
            other.data = 0;
        };

        T& operator[](const int index){
            if(index < 0 || index > size - 1)
                throw std::runtime_error("sample int exception: index out of range");
            return *(data + index);
        };
        T operator[](const int index) const{
            if(index < 0 || index > size - 1)
                        throw std::runtime_error("sample int exception: index out of range");
            return *(data + index);
        };

        friend std::ostream& operator<<(std::ostream& out, const __sample& test){
            out << "Sample data";
            if(test.size != 0)
                out << " (size = " << test.size << "):\n";
            for(int i = 0; i < test.size; i++)
                out << test[i] << ' ';
            out << '\n';
            return out;
        };
        friend std::ostream& operator<<(std::ostream& out, const __sample* test){
            return(out << (*test));
        };
        __sample& operator=(const __sample& other){
            T* tmp = (T*)malloc(sizeof(T) * other.size);
            memcpy(tmp, other.data, sizeof(T) * other.size);
            if(data != 0)
                free(data);
            size = other.size;
            data = tmp;
            tmp = 0;
            return *this;
        };
        ~__sample(){
            free(data);
        };
    };

    using _sample = __sample<int>;
};

#endif // SAMPLE_STRUCT_HPP
