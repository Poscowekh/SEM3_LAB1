#include <iostream>
#include "Structures.hpp"
#include "Sorter.hpp"
#include "testing/tests/Tests.hpp"

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

int _sample_init_func(const int index){
    return (index + 1) * (index + 1);
};
/*
template<typename Container>
bool _assert_sorted(const Container& container){
    if(container.size() < 2)
        return true;
    auto
        iter1 = container.begin(),
        iter2 = ++(container.begin()),
        end = container.end();
    while(iter2 != end)
        if(*iter2++ < *iter1++)
            return false;
    return true;
};
*/
template<typename Container>
bool _assert_sorted(const Container container){
    if(container->size() < 2)
        return true;
    auto
        iter1 = container->begin(),
        iter2 = ++(container->begin()),
        end = container->end();
    while(iter2 != end)
        if(*iter2++ < *iter1++)
            return false;
    return true;
};

int main(){

    srand(time(0));
    int size = 10000;
    _sample test = _sample(size);
    //cout << test;

    //S* seq1 = new AS(test.data, test.size);
    S* seq = new LS(test.data, test.size);
    S* seq1 = new LS(seq);
    S* seq2 = new LS(seq);
    S* seq3 = new LS(seq);
    //cout << seq1 << seq2;

    //cout << "time taken: " << _get_time_micro(BubbleSort<int>, seq1, StdComparator<int>) << " microseconds\n";
    cout << "time taken: " << _get_time_micro(QuickSort<int>, seq2, StdComparator<int>) << " microseconds\n";
    cout << "time taken: " << _get_time_micro(SelectionSort<int>, seq3, StdComparator<int>) << " microseconds\n";
    if(!_assert_sorted(seq3) || !_assert_sorted(seq2))
        cout << "ERROR NOT SORTED\n";

    //cout << seq3;
    //Test::Tester test_main = Test::create_tester();
    //test_main.run_tests();
    //cout << Test::test_array_create();

    /*size = 2000;
    test = _sample(size);
    seq = new LS(test.data, test.size);
    seq1 = new LS(seq);
    seq2 = new LS(seq);
    cout << "\ntime taken: " << _get_time_micro(BubbleSort<int>, seq1, StdComparator<int>) << " microseconds\n";
    cout << "time taken: " << _get_time_micro(ShakerSort<int>, seq2, StdComparator<int>) << " microseconds\n";

    size = 3000;
    test = _sample(size);
    seq = new LS(test.data, test.size);
    seq1 = new LS(seq);
    seq2 = new LS(seq);
    cout << "\ntime taken: " << _get_time_micro(BubbleSort<int>, seq1, StdComparator<int>) << " microseconds\n";
    cout << "time taken: " << _get_time_micro(ShakerSort<int>, seq2, StdComparator<int>) << " microseconds\n";

    size = 4000;
    test = _sample(size);
    seq = new LS(test.data, test.size);
    seq1 = new LS(seq);
    seq2 = new LS(seq);
    cout << "\ntime taken: " << _get_time_micro(BubbleSort<int>, seq1, StdComparator<int>) << " microseconds\n";
    cout << "time taken: " << _get_time_micro(ShakerSort<int>, seq2, StdComparator<int>) << " microseconds\n";*/

    //cout << seq2;

    //cout << seq2->sub_sequence(1,2)->get_concated(seq1);
    //cout << seq1->get_concated(seq2->sub_sequence(1,2));\

    return 0;
};
