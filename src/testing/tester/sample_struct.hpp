#ifndef SAMPLE_STRUCT_HPP
#define SAMPLE_STRUCT_HPP
#include <iostream>

namespace Test {
    struct _sample {
        int* data;
        int size;

        _sample(const int _size) : size(_size), data((int*)malloc(sizeof(int) * _size)) {
            for(int i = 0; i < size; i++){
                int r = rand();
                memcpy(data + i, &r, sizeof(int));
            };
        };
        explicit _sample(_sample&& other) : size(other.size), data(other.data) {
            other.data = 0;
        };

        int& operator[](const int index){
            if(index < 0 || index > size - 1)
                throw std::runtime_error("sample int exception: index out of range");
            return *(data + index);
        };
        int operator[](const int index) const{
            if(index < 0 || index > size - 1)
                        throw std::runtime_error("sample int exception: index out of range");
            return *(data + index);
        };

        friend std::ostream& operator<<(std::ostream& out, const _sample& test){
            out << "Sample data";
            if(test.size != 0)
                out << " (size = " << test.size << " ):\n";
            for(int i = 0; i < test.size; i++)
                out << test[i] << ' ';
            out << '\n';
            return out;
        };
        _sample& operator=(const _sample& other){
            int* tmp = (int*)malloc(sizeof(int) * other.size);
            memcpy(tmp, other.data, sizeof(int) * other.size);
            if(data != 0)
                free(data);
            size = other.size;
            data = tmp;
            tmp = 0;
            return *this;
        };
        ~_sample(){
            free(data);
        };
    };
};

#endif // SAMPLE_STRUCT_HPP
