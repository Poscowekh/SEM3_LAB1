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

    Array<Sort>* funcs = new Array<Sort>();
    Sequence sequence = 0;
    Comparator comparator = StdComparator<T>;

    Sorter(const Sorter&) = delete;

    void _print_sort_names() const{
        using std::cout;
        using std::endl;

        for(int i = 0; i < funcs->size(); ++i)
            cout << "   " << i + 1 << ": " << funcs->get(i).name() << endl;
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
        if(choise < 0 || choise > funcs->size()) {
            cout << "Wrong input, try again...\n";
            return _choose_sort();
        };
        cout << endl;

        return choise;
    };

public:
    Sorter() : funcs(new Array<Sort>()), sequence(0), comparator(StdComparator<T>) {};
    Sorter(Sorter&& other) : funcs(other.funcs), sequence(other.sequence), comparator(other.comparator) {
        other.funcs = 0;
    };

    void add_sort(const Sort* function){
        funcs->push_back(function);
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

    Sequence operator()(bool show_time = true) const{
        int choise = _choose_sort() - 1;
        Sequence copy = sequence->get_copy();
        long long result = _sort_time(funcs->get(choise), copy, comparator);

        if(show_time){
            std::string output = std::string();
            output += "time taken: ";
            output += std::to_string(result);
            output += " milliseconds\n";
            std::cout << output;
        };

        return copy;
    };
    Sort operator[](const int sort_index) const{
        return funcs->get(sort_index);
    };

    int count() const{
        return funcs->size();
    };

    ~Sorter(){
        delete funcs;
        sequence = 0;
        delete sequence;
    };
};

Sorter<double> _basic_sorter(){
    Sorter<double> sorter = Sorter<double>();

    sorter.add_sort(bubble_sort);
    sorter.add_sort(shaker_sort);
    sorter.add_sort(insertion_sort);
    sorter.add_sort(selection_sort);
    sorter.add_sort(quick_sort);
    sorter.add_sort(merge_sort);

    return sorter;
};

#endif // SORTER_HPP
