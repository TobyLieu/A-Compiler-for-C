#include "Lexical_analyzer.h"
using namespace std;

int main() {
    int state = 1, state_before = 0;
    ifstream in("demo.c");
    if (!in.is_open()) {
        cout << "File can't be opened!" << endl;
        exit(1);
    }
    ofstream out("tokens.txt");
    if (!out.is_open()) {
        cout << "File error!" << endl;
        exit(1);
    }

    Lexical_analyzer my_lex;
    string token = "";
    int code;
    char ch;

    while (!in.eof()) {
        ch = in.get();
        // cout << ch << endl;
        state_before = state;
        state = my_lex.state_change(state, ch);
        // cout << state << "  " << ch << endl;
        if (state) {
            if (ch != ' ' && ch != '\n' && ch != '\t') token += ch;
        } else {
            in.seekg(-1, ios::cur);
            code = my_lex.state_to_code(state_before, token);
            if (code == -1) break;
            out << token << "    ";
            out << setw(2) << setfill('0') << code << endl;
            token = "";
            state = 1;
        }
    }

    return 0;
}