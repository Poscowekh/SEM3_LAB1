#include <iostream>
#include "Structures.hpp"
#include "Sorter.hpp"

using namespace std;

using LS = ListSequence<int>;
using AS = ArraySequence<int>;
using L = List<int>;
using A = Array<int>;
using S = Sequence<int>;

#include <random>
#include <time.h>

struct _sample{
    int* data;
    const int size;
    _sample(const int _size) : size(_size), data((int*)malloc(sizeof(int) * _size)) {
        for(int i = 0; i < size; i++){
            int r = rand();
            memcpy(data + i, &r, sizeof(int));
        };
    };
    int& operator[](const int index){
        if(index < 0 || index > size - 1)
            throw runtime_error("sample int exception: index out of range");
        return *(data + index);
    };
    int operator[](const int index) const{
        if(index < 0 || index > size - 1)
                    throw runtime_error("sample int exception: index out of range");
        return *(data + index);
    };
    friend ostream& operator<<(ostream& out, const _sample& test){
        for(int i = 0; i < test.size; i++)
            out << test[i] << ' ';
        out << '\n';
        return out;
    };
};

int _sample_init_func(const int index){
    return (index + 1) * (index + 1);
};

int main()
{
    srand(time(0));
    int size = 10;
    _sample test = _sample(size);
    cout << test;

    S* seq1 = new AS(test.data, test.size);
    S* seq2 = new LS(seq1);
    cout << seq1 << seq2;
    //cout << seq2->sub_sequence(1,2)->get_concated(seq1);
    //cout << seq1->get_concated(seq2->sub_sequence(1,2));


    return 0;
};
