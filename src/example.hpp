#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP
#include "Sorter.hpp"

void example() {
    using std::cout;
    srand(time(0));
    const int size = rand() % 5000 + 2500;
    Testing::__sample<double> data = Testing::__sample<double>(size);
    Sequence<double>* list = new ListSequence<double>(data.data, size);
    Sequence<double>* array = new ArraySequence<double>(data.data, size);
    cout << "Generated sequence of " << size << " double values.\n";

    Sorter<double> list_sorter = _basic_sorter();
    list_sorter.set_sequence(list);
    Sorter<double> array_sorter = _basic_sorter();
    array_sorter.set_sequence(array);

    cout << "\nSorting ListSequence...\n";
    for(int i = 0; i < list_sorter.count(); ++i) {
        Sequence<double>* copy = list->get_copy();
        cout << "Using " << list_sorter[i].name() << ": " << _sort_time(list_sorter[i], copy) << " milliseconds.:\n";// << copy;
        delete copy;
    };

    cout << "\nSorting ArraySequence...\n";
    for(int i = 0; i < array_sorter.count(); ++i) {
        Sequence<double>* copy = array->get_copy();
        cout << "Using " << array_sorter[i].name() << ": " << _sort_time(array_sorter[i], copy) << " milliseconds.:\n";// << copy;
        delete copy;
    };

    delete list;
    delete array;
};

#endif // EXAMPLE_HPP
