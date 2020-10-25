#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include "testing/tests/Tests.hpp"
#include "Sorter.hpp"
#include "example.hpp"

class Interface {
private:
    using Sorter = Sorter<double>;
    using Sequence = Sequence<double>;
    using ASequence = ArraySequence<double>;
    using LSequence = ListSequence<double>;
    using Comparator = Comparator<double>;
    using Sample = Testing::__sample<double>;

    Sorter* list_sorter = 0;
    Sorter* array_sorter = 0;
    int sequence_switch = 0;
    Sequence* my_sequence1 = 0;
    Sequence* my_sequence2 = 0;


    int _get_print() {
        using std::cin;
        using std::cout;

        int choise = 0;

        try {
            cin >> choise;
        } catch (...) {
            cout << "Wrong input, try again...\n";
            return _get_print();
        }
        if(choise < 0 || choise > 1){
            cout << "Wrong input, try again...\n";
            return _get_print();
        };

        return choise;
    }
    void sort_sequence() {
        using std::cout;
        using std::cin;
        using std::endl;

        Sequence* copy = 0;

        if(sequence_switch == 1){
            array_sorter->set_sequence(my_sequence1);
            copy = array_sorter->operator()(true);
        } else if(sequence_switch == 2) {
            list_sorter->set_sequence(my_sequence1);
            copy = list_sorter->operator()(true);
        } else {
            array_sorter->set_sequence(my_sequence1);
            array_sorter->operator()(true);
            list_sorter->set_sequence(my_sequence2);
            copy = list_sorter->operator()(true);
        };

        cout << "A copy of your sequence was sorted.\n";
        cout << "Print sorted sequence?\n    0: yes\n    1: no\nChosen: ";
        int choise = _get_print();
        if(choise == 0) {
            cout << "Sorted copy of your sequence:\n" << copy;
        };
        cout << endl;

        call_funcs(choose_action());
    };
    int get_seed() {
        using std::cout;
        using std::cin;
        using std::endl;

        cout << "Choose a seed:\n";
        int seed = -1;

        try {
            cin >> seed;
        } catch (...) {
            cout << "Wrong input, try again...\n";
            return get_seed();
        }
        if(seed < 0 || seed > INT_MAX){
            cout << "Wrong input, try again...\n";
            return get_seed();
        };

        return seed;
    };
    double _get_value() {
        using std::cout;
        using std::cin;
        using std::endl;

        double value = 0.0;
        try {
            cin >> value;
        } catch (...) {
            cout << "Wrong input, try again...\n";
            return _get_value();
        }

        return value;
    };
    void manual_gen() {
        using std::cout;
        using std::cin;
        using std::endl;

        cout << "Start entering " << my_sequence1->size() << " values:\n";
        auto iter1 = my_sequence1->begin(), iter2 = iter1;
        if(sequence_switch == 3)
            auto iter2 = my_sequence2->begin();
        for(int i = 0; i < my_sequence1->size(); ++i, ++iter1){
            cout << "   " << i + 1 << ": ";
            double value = _get_value();
            *iter1 = value;
            if(sequence_switch == 3){
                *iter2 = value;
                ++iter2;
            };
        };

        cout << endl;

        call_funcs(choose_action());
    };
    void random_seed_gen() {
        using std::cout;
        using std::cin;
        using std::endl;

        int choise = -1;

        cout << "Choose seed:\n";
        cout << "   0: Go back to choosing a way to generate a sequence\n";
        cout << "   1: Seed from current system time\n";
        cout << "   2: Manual seed input\n";
        cout << "Chosen: ";

        try {
            cin >> choise;
        } catch (...) {
            cout << "Wrong input, try again...\n";
            random_seed_gen();
        }
        if(choise < 0 || choise > 2){
            cout << "Wrong input, try again...\n";
            random_seed_gen();
        };

        cout << endl;

        int seed = 0;
        switch(choise) {
        case 0:
            choose_how_to_create();
            return;
        case 1:
            seed = time(0);
            break;
        case 2:
            seed = get_seed();
            break;
        };

        Sample tmp = Sample(my_sequence1->size(), seed);

        if(sequence_switch == 1)
            my_sequence1 = new ASequence(tmp.data, tmp.size);
        else if(sequence_switch == 2)
            my_sequence1 = new LSequence(tmp.data, tmp.size);
        else {
            my_sequence1 = new ASequence(tmp.data, tmp.size);
            my_sequence2 = new LSequence(my_sequence1);
        };

        cout << "Sequence created.\n\n";

        call_funcs(choose_action());
    };
    int choose_size() {
        using std::cout;
        using std::cin;
        using std::endl;

        int choise = -1;

        cout << "Enter valid size or a negative number to go back:\nSize = ";

        try {
            cin >> choise;
        } catch (...) {
            cout << "Wrong input, try again...\n";
            return choose_size();
        }
        if(choise > INT_MAX || choise == 0){
            cout << "Wrong input, try again...\n";
            return choose_size();
        };

        if(choise < 0) {
            choose_type();
            exit(100);
        };

        cout << endl;

        return choise;
    };
    void choose_how_to_create() {
        using std::cout;
        using std::cin;
        using std::endl;

        int choise = -1;

        cout << "Choose how to create your sequence(-s):\n";
        cout << "   0: Go back to type choise\n";
        //cout << "   1: Go back to size choise";
        cout << "   1: Random seed generation\n";
        cout << "   2: Manual input\n";
        cout << "Chosen: ";

        try {
            cin >> choise;
        } catch (...) {
            cout << "Wrong input, try again...\n";
            choose_how_to_create();
        }
        if(choise < 0 || choise > 2){
            cout << "Wrong input, try again...\n";
            choose_how_to_create();
        };

        cout << endl;

        switch(choise) {
        case 0:
            choose_type();
            break;
        case 1:
            random_seed_gen();
            break;
        case 2:
            manual_gen();
            break;
        };
    };
    void choose_type() {
        using std::cout;
        using std::cin;
        using std::endl;

        int choise = -1;

        cout << "Choose sequence type:\n";
        cout << "   0: Go back to choises\n";
        cout << "   1: ArraySequence\n";
        cout << "   2: ListSequence\n";
        cout << "   3: Both(creates a copy for each type)\n";
        cout << "Chosen: ";

        try {
            cin >> choise;
        } catch (...) {
            cout << "Wrong input, try again...\n";
            choose_type();
        }
        if(choise < 0 || choise > 3){
            cout << "Wrong input, try again...\n";
            choose_type();
        };

        sequence_switch = choise;
        int size = 0;
        if(choise > 0) {
            cout << endl;
            size = choose_size();
        };

        switch(choise) {
        case 0:
            cout << endl;
            call_funcs(choose_action());
            return;
        case 1:
            my_sequence1 = new ASequence(size);
            break;
        case 2:
            my_sequence1 = new LSequence(size);
            break;
        case 3:
            my_sequence1 = new ASequence(size);
            my_sequence2 = new LSequence(size);
            break;
        };

        choose_how_to_create();
    };

    int choose_action() const{
        using std::cout;
        using std::cin;

        int choise = -1;

        cout << "Choose action:\n";
        cout << "   0: exit\n";
        cout << "   1: run example\n";
        cout << "   2: run tests\n";
        cout << "   3: create sequence\n";
        if(sequence_switch > 0){
            cout << "   4: sort my sequence(-s)\n";
            cout << "   5: print my sequence(-s)\n";
        };
        cout << "Chosen: ";

        try {
            cin >> choise;
        } catch (...) {
            cout << "Wrong input, try again...\n";
            return choose_action();
        }
        if(choise < 0 || (sequence_switch > -1 && choise > 5) || (sequence_switch == -1 && choise > 3)) {
            cout << "Wrong input, try again...\n";
            return choose_action();
        };

        cout << std::endl;

        return choise;
    };
    void call_funcs(const int choise){
        using std::cout;
        using std::endl;

        switch(choise){
        case 0:
            cout << "Goodbye!";
            exit(0);
        case 1:
            example();
            cout << endl << endl;
            break;
        case 2:
            Testing::tester();
            cout << endl << endl;
            break;
        case 3:
            choose_type();
            break;
        case 4:
            sort_sequence();
            break;
        case 5:
            cout << my_sequence1 << endl;
            break;
        };
        call_funcs(choose_action());
    };

    Interface(const Interface&) = delete;
    Interface(Interface&&) = delete;

public:
    Interface() : list_sorter(new Sorter(_basic_sorter())), array_sorter(new Sorter(_basic_sorter())) {};

    void operator()(){
        call_funcs(choose_action());
    };

    ~Interface(){
        delete list_sorter;
        delete array_sorter;
        delete my_sequence1;
        delete my_sequence2;
    };
};

#endif // INTERFACE_HPP
