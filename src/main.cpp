//#include <iostream>
//#include "Structures.hpp"
#include "Interface.hpp"
//#include "testing/tests/Tests.hpp"
/*
using namespace std;

using LS = ListSequence<int>;
using AS = ArraySequence<int>;
using L = List<int>;
using A = Array<int>;
using S = Sequence<int>;

#include <random>
#include <time.h>
//#include <sysinfoapi.h>

int _sample_init_func(const int index){
    return (index + 1) * (index + 1);
};
template<typename Func>
void do_a_sort_micro(const S* sequence, Func func) {
    S* copy = sequence->get_copy();
    string output = string();
    output += "time taken: ";
    output += to_string(_get_time_micro(func, copy, StdComparator<int>));
    output += " microseconds\n";
    if(!Testing::_assert_sorted(copy))
        cout << "ERROR NOT SORTED\n";
    //delete copy;
    cout << output;
};
template<typename Func>
void do_a_sort_milli(const S* sequence, Func func) {
    S* copy = sequence->get_copy();
    string output = string();
    output += "time taken: ";
    output += to_string(_get_time_milli(func, copy, StdComparator<int>));
    output += " milliseconds\n";
    if(!Testing::_assert_sorted(copy))
        cout << "ERROR NOT SORTED\n";
    delete copy;
    cout << output;
};

template<typename Func>
void do_a_sort_micro_for_both(const S* list, const S* array, Func func) {
    do_a_sort_micro(list, func);
    do_a_sort_micro(array, func);
};
template<typename Func>
void do_a_sort_milli_for_both(const S* list, const S* array, Func func) {
    do_a_sort_milli(list, func);
    do_a_sort_milli(array, func);
};*/

int main(){
    Interface* interface = new Interface();
    (*interface)();

    return 0;
};
