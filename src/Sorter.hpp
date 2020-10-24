#ifndef SORTER_HPP
#define SORTER_HPP
#include "Structures.hpp"
#include "Sorts.hpp"

template<typename T = double>
class Sorter {
private:
    using Sequence = Sequence<T>*;
    using Comparator = Comparator<T>;
    using Sort = SortFunction<T>;

    Sort* funcs = 0;
    int count = 0;
    Sequence sequence = 0;
    Comparator comparator = StdComparator<T>;

    Sorter(const Sorter&) = delete;

    void _realloc(const int _count = 1){
        Sort* tmp = (Sort*)malloc((count + _count) * sizeof(Sort));
        memcpy(tmp, funcs, count * sizeof(Sort));
        free(funcs);
        funcs = tmp;
        tmp = 0;
    };
    void _print_sort_names() const{
        using std::cout;
        using std::endl;

        for(int i = 0; i < count; i++)
            cout << "   " << i + 1 << ": " << (funcs + i)->name() << endl;
    };
    int _choose_sort() const{
        using std::cout;
        using std::cin;
        using std::endl;

        int choise = -1;

        cout << "Choose a sorting algorythm:\n";
        _print_sort_names();
        cout << "Chosen: ";
        try {
            cin >> choise;
        } catch (...) {
            cout << "Wrong input, try again...\n";
            return _choose_sort();
        }
        if(choise < 0 || choise > count)
            cout << "Wrong input, try again...\n";
            return _choose_sort();
        cout << endl;

        return choise;
    };

public:
    Sorter() : funcs(0), count(0), sequence(0), comparator(StdComparator<T>) {};
    Sorter(Sorter&& other) : funcs(other.funcs), count(other.count),
        sequence(other.sequence), comparator(other.comparator) {
        other.funcs = 0;
    };

    void add_sort(const Sort* function){
        _realloc();
        memcpy(funcs, function, sizeof(Sort));
        ++count;
    };
    void add_sort(const Sort& function){
        add_sort(&function);
    };

    void set_sequence(Sequence _sequence){
        sequence = _sequence;
    };
    void set_comparator(Comparator _comparator){
        comparator = _comparator;
    };

    long long operator()(bool show_time = true) const{
        int choise = _choose_sort();
        Sequence copy = sequence->get_copy();
        long long result = _get_time_micro(*(funcs + choise), copy, comparator);

        if(show_time){
            std::string output = std::string();
            output += "time taken: ";
            output += std::to_string(result);
            output += " microseconds\n";
            std::cout << output;
        };
        delete copy;
        return result;
    };

    ~Sorter(){
        free(funcs);
        sequence = 0;
        delete sequence;
    };
};

#endif // SORTER_HPP
