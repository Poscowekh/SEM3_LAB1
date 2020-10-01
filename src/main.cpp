#include <iostream>
#include "Structures.hpp"
#include "Sorter.hpp"

using namespace std;

using LS = ListSequence<int>;
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

        //ARRAY CHECK
    A a = A(test.data, test.size);
    A aa = A(&a);
    A sum = a + aa;

    sum += 100;
    sum = 100 + sum;
    sum.resize(5);
    cout << sum;
    a = sum.subarray(2,4);
    cout << a;

    /*  //LIST CHECK
    L list = L(data, size);
    cout << list << endl;

    auto iter = list.begin();
    auto end = list.end();
    while(*iter != *end){
        cout << *iter << ' ';
        (*iter)++;
    };*/
    /*  //SEQUENCE CHECK
    S* seq1 = new LS(test.data, test.size);
    S* seq2 = new LS(seq1);
    S* seq3 = new LS();
    S* seq4 = new LS{ 1, 2, 3 };
    S* seq5 = new LS(5, _sample_init_func);
    S* seq6 = new LS();
    cout << seq1 << endl << seq2 << endl << seq3 << endl << seq4 << endl << seq5;
    cout << endl << *seq1 + (*seq4) << endl << seq5->sub_sequence(0,4);*/

    return 0;
};
