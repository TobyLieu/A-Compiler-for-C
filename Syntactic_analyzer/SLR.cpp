#include "SLR.h"
#include "Lexical_analyzer.h"
using namespace std;

queue<string> DigitExpressionParser_SLR::lex2Str(string file_name) {
    int state = 1, state_before = 0;
    queue<string> ans;
    ifstream in(file_name);
    if (!in.is_open()) {
        cout << "File can't be opened!" << endl;
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
            if (find(T.begin(), T.end(), token) != T.end()) {
                ans.push(token);
            } else {
                ans.push("i");
            }
            token = "";
            state = 1;
        }
    }
    ans.push("#");
    return ans;
}

void DigitExpressionParser_SLR::pop(queue<string> &q, int num) {
    for (int i = 0; i < num; i++) {
        q.pop();
    }
}
void DigitExpressionParser_SLR::pop(stack<string> &s, int num){
    for (int i = 0; i < num; i++) {
        s.pop();
    }
}
void DigitExpressionParser_SLR::pop(stack<State> &s, int num){
    for (int i = 0; i < num; i++) {
        s.pop();
    }
}

bool DigitExpressionParser_SLR::_init(string file_name) {
    characters = lex2Str(file_name);
    states.push(0);
    entered.push("#");
    return true;
}

void DigitExpressionParser_SLR::initialMaps() {
    const string actions[25][10]{
        {"s5", "", "s7", "s8", "", "", "", "", "s6", ""},
        {"", "", "s9", "s10", "", "", "", "", "", "acc"},
        {"", "r4", "r4", "r4", "s11", "s12", "s13", "", "", "r4"},
        {"", "r8", "r8", "r8", "r8", "r8", "r8", "", "", "r8"},
        {"", "r10", "r10", "r10", "r10", "r10", "r10", "s14", "", "r10"},
        {"s5", "", "s7", "s8", "", "", "", "", "s6", ""},
        {"", "r12", "r12", "r12", "r12", "r12", "r12", "r12", "", "r12"},
        {"", "", "", "", "", "", "", "", "s16", ""},
        {"", "", "", "", "", "", "", "", "s17", ""},
        {"s5", "", "s7", "s8", "", "", "", "", "s6", ""},
        {"s5", "", "s7", "s8", "", "", "", "", "s6", ""},
        {"s5", "", "s7", "s8", "", "", "", "", "s6", ""},
        {"s5", "", "s7", "s8", "", "", "", "", "s6", ""},
        {"s5", "", "s7", "s8", "", "", "", "", "s6", ""},
        {"s5", "", "s7", "s8", "", "", "", "", "s6", ""},
        {"", "s23", "s9", "s10", "", "", "", "", "", ""},
        {"", "r13", "r13", "r13", "r13", "r13", "r13", "r13", "", "r13"},
        {"", "r14", "r14", "r14", "r14", "r14", "r14", "r14", "", "r14"},
        {"", "r2", "r2", "r2", "s11", "s12", "s13", "", "", "r2"},
        {"", "r3", "r3", "r3", "s11", "s12", "s13", "", "", "r3"},
        {"", "r5", "r5", "r5", "r5", "r5", "r5", "", "", "r5"},
        {"", "r6", "r6", "r6", "r6", "r6", "r6", "", "", "r6"},
        {"", "r7", "r7", "r7", "r7", "r7", "r7", "", "", "r7"},
        {"", "r11", "r11", "r11", "r11", "r11", "r11", "r11", "", "r11"},
        {"", "r9", "r9", "r9", "r9", "r9", "r9", "", "", "r9"},
    };

    const int gotos[25][4] = {
        {1, 2, 3, 4},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {15, 2, 3, 4},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, 18, 3, 4},
        {-1, 19, 3, 4},
        {-1, -1, 20, 4},
        {-1, -1, 21, 4},
        {-1, -1, 22, 4},
        {-1, -1, 24, 4},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
        {-1, -1, -1, -1},
    };

    for (int i = 0; i < 25; i++) {
        ActionMap a;
        GotoMap g;
        for (int j = 0; j < 10; j++) {
            a[T[j]] = parse2Action(actions[i][j]);
        }

        for (int k = 0; k < 4; k++) {
            g[V[k]] = gotos[i][k];
        }
        am.push_back(a);
        gm.push_back(g);
    }
}

Action DigitExpressionParser_SLR::parse2Action(string s) {
    if (s.length() == 0 || s.length() > 3) {
        return Action{Error, Error};
    }
    char kind = tolower(s[0]);
    int id;
    if (kind == 'r' || kind == 's') {
        id = stoi(s.substr(1, s.length() - 1));
    }

    switch (kind) {
        case 'r':
            return Action{Reduce, id};
        case 's':
            return Action{Shift, id};
        case 'a':
            return Action{Accpet, Accpet};
        default:
            return Action{Error, Error};
    }
}

void DigitExpressionParser_SLR::printProducer(int id) { cout << producers[id].first << "->" << producers[id].second << endl; }

DigitExpressionParser_SLR::DigitExpressionParser_SLR() { initialMaps(); }

bool DigitExpressionParser_SLR::parse(string file_name) {
    if (!_init(file_name)) {
        cerr << "Error: can not open the file" << endl;
        return false;
    }

    while (true) {
        State curState = states.top();
        string curCharacter = characters.front();

        auto &action = am[curState][curCharacter];
        cout << curState << " " << curCharacter << " " << action.kind << " " << action.id << endl;

        switch (action.kind) {
            case Shift:
                states.push(action.id);
                entered.push(curCharacter);
                characters.pop();
                break;

            case Reduce: {
                // use producer[id] to reduce
                printProducer(action.id - 1);
                auto producer = producers[action.id - 1];
                int popNum = producer.second.size();
                cout << popNum << endl;
                pop(states, popNum);
                pop(entered, popNum);
                entered.push(producer.first);

                states.push(gm[states.top()][producer.first]);
            } break;

            case Error:
                if(curCharacter == "i"){
                    cout << "Missing operator" << endl;
                    return false;
                }

                switch (curState)
                {
                case 1:
                    cout << "Missing left parenthesis" << endl;
                    break;

                case 15:
                    cout << "Missing right parenthesis" << endl;
                    break;

                default:
                    cout << "Missing operand" << endl;
                    break;
                }
                return false;

            case Accpet:
                cout << "Accepted" << endl;
                return true;
        }
    }
}