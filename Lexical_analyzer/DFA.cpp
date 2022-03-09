#include "DFA.h"

unordered_map<int, unordered_map<string, int>> transition_table;
vector<char> symbol = {'+', '-', '*', '/', '%', '!', '=', '>', '<', '&', '|', '^', '~', '?', '{', '}', '[', ']', '(', ')', ',', ';', '\\'};

void initialize_state_1() {
    unordered_map<string, int> tmp;
    tmp[" "] = 1;
    tmp["\n"] = 1;
    tmp["\t"] = 1;
    for (int i = 'A'; i <= 'Z'; i++) {
        tmp["" + i] = 2;
    }
    for (int i = 'a'; i <= 'z'; i++) {
        tmp["" + i] = 2;
    }
    for (int i = '0'; i <= '9'; i++) {
        tmp["" + i] = 3;
    }
    tmp["\'"] = 10;
    tmp["\""] = 13;
    for (int i = 0; i < symbol.size(); i++) {
        tmp["" + symbol[i]] = 16;
    }
    transition_table[1] = tmp;
}

void initialize_state_2() {
    unordered_map<string, int> tmp;
    for (int i = 'A'; i <= 'Z'; i++) {
        tmp["" + i] = 2;
    }
    for (int i = 'a'; i <= 'z'; i++) {
        tmp["" + i] = 2;
    }
    for (int i = '0'; i <= '9'; i++) {
        tmp["" + i] = 2;
    }
    transition_table[2] = tmp;
}

void initialize_state_3() {
    unordered_map<string, int> tmp;
    for (int i = '0'; i <= '9'; i++) {
        tmp["" + i] = 3;
    }
    tmp["."] = 4;
    tmp["e"] = 6;
    transition_table[3] = tmp;
}

void initialize_state_4() {
    unordered_map<string, int> tmp;
    for (int i = '0'; i <= '9'; i++) {
        tmp["" + i] = 5;
    }
    transition_table[4] = tmp;
}

void initialize_state_5() {
    unordered_map<string, int> tmp;
    for (int i = '0'; i <= '9'; i++) {
        tmp["" + i] = 5;
    }
    tmp["e"] = 6;
    transition_table[5] = tmp;
}

void initialize_state_6() {
    unordered_map<string, int> tmp;
    for (int i = '0'; i <= '9'; i++) {
        tmp["" + i] = 7;
    }
    tmp["-"] = 8;
    transition_table[6] = tmp;
}

void initialize_state_7() {
    unordered_map<string, int> tmp;
    for (int i = '0'; i <= '9'; i++) {
        tmp["" + i] = 7;
    }
    transition_table[7] = tmp;
}

void initialize_state_8() {
    unordered_map<string, int> tmp;
    for (int i = '0'; i <= '9'; i++) {
        tmp["" + i] = 9;
    }
    transition_table[8] = tmp;
}

void initialize_state_9() {
    unordered_map<string, int> tmp;
    for (int i = '0'; i <= '9'; i++) {
        tmp["" + i] = 9;
    }
    transition_table[9] = tmp;
}

void initialize_state_10() {
    unordered_map<string, int> tmp;
    for (int i = 0; i <= 127; i++) {
        tmp["" + i] = 11;
    }
    transition_table[10] = tmp;
}

void initialize_state_11() {
    unordered_map<string, int> tmp;
    tmp["\'"] = 12;
    transition_table[11] = tmp;
}

void initialize_state_12() {
    unordered_map<string, int> tmp;
    transition_table[11] = tmp;
}

void initialize_state_13() {
    unordered_map<string, int> tmp;
    for (int i = 0; i <= 127; i++) {
        tmp["" + i] = 14;
    }
    transition_table[13] = tmp;
}

void initialize_state_14() {
    unordered_map<string, int> tmp;
    for (int i = 0; i <= 127; i++) {
        tmp["" + i] = 14;
    }
    tmp["\""] = 15;
    transition_table[14] = tmp;
}

void initialize_state_15() {
    unordered_map<string, int> tmp;
    transition_table[15] = tmp;
}

void initialize_state_16() {
    unordered_map<string, int> tmp;
    for (int i = 0; i <= symbol.size(); i++) {
        tmp["" + i] = 16;
    }
    transition_table[16] = tmp;
}

void initialize_DFA() {
    initialize_state_1();
    initialize_state_2();
    initialize_state_3();
    initialize_state_4();
    initialize_state_5();
    initialize_state_6();
    initialize_state_7();
    initialize_state_8();
    initialize_state_9();
    initialize_state_10();
    initialize_state_11();
    initialize_state_12();
    initialize_state_13();
    initialize_state_14();
    initialize_state_15();
    initialize_state_16();
}