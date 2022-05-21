#include "LL1.h"

#include "Lexical_analyzer.h"
using namespace std;

queue<string> DigitExpressionParser_LL1::lex2Str(string file_name) {
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
            ans.push(token);
            token = "";
            state = 1;
        }
    }
    ans.push("#");
    return ans;
}

bool DigitExpressionParser_LL1::is_i(string &token) {
    if (find(T.begin(), T.end(), token) != T.end()) {
        return false;
    } else {
        return true;
    }
}

void DigitExpressionParser_LL1::push(stack<Syn_type> &SYN, vector<Syn_type> list, string &curCharacter) {
    for (int i = list.size() - 1; i >= 0; i--) {
        if (list[i].character == "") continue;
        if (list[i].character == "i") list[i].character = curCharacter;
        SYN.push(list[i]);
    }
}

bool DigitExpressionParser_LL1::_init(string file_name) {
    characters = lex2Str(file_name);
    SYN.push(Syn_type(Symbol, "#"));
    SYN.push(Syn_type(Symbol, "E"));
    return true;
}

void DigitExpressionParser_LL1::initialMaps() {
    // const int m[7][10] = {{0, 0, 0, -1, -1, -1, -1, -1, 0, -1}, {-1, 1, 2, -1, -1, -1, -1, 3, -1, 3}, {4, 4, 4, -1, -1, -1, -1, -1, 4, -1}, {-1, 8, 8, 5, 6, 7, -1, 8, -1, 8}, {9, 9, 9, -1, -1, -1, -1, -1, 9, -1}, {-1, 11, 11, 11, 11, 11, 10, 11, -1, 11}, {12, 14, 15, -1, -1, -1, -1, -1, 13, -1}};

    // row E
    vector<Syn_type> v1(2);
    v1[0] = Syn_type(Symbol, "T");
    v1[1] = Syn_type(Symbol, "E'");

    unordered_map<string, vector<Syn_type>> m1;
    m1["("] = v1;
    m1["+"] = v1;
    m1["-"] = v1;
    m1["i"] = v1;

    analysis_map["E"] = m1;

    // row E'
    vector<Syn_type> v2(4);
    v2[0] = Syn_type(Symbol, "+");
    v2[1] = Syn_type(Symbol, "T");
    v2[2] = Syn_type(Operation, "+", GEQ);
    v2[3] = Syn_type(Symbol, "E'");

    vector<Syn_type> v3(4);
    v3[0] = Syn_type(Symbol, "-");
    v3[1] = Syn_type(Symbol, "T");
    v3[2] = Syn_type(Operation, "-", GEQ);
    v3[3] = Syn_type(Symbol, "E'");

    vector<Syn_type> v4(1);
    v4[0] = Syn_type(Symbol, "");

    unordered_map<string, vector<Syn_type>> m2;
    m2["+"] = v2;
    m2["-"] = v3;
    m2[")"] = v4;
    m2["#"] = v4;

    analysis_map["E'"] = m2;

    // row T
    vector<Syn_type> v5(2);
    v5[0] = Syn_type(Symbol, "F");
    v5[1] = Syn_type(Symbol, "T'");

    unordered_map<string, vector<Syn_type>> m3;
    m3["("] = v5;
    m3["+"] = v5;
    m3["-"] = v5;
    m3["i"] = v5;

    analysis_map["T"] = m3;

    // row T'
    vector<Syn_type> v6(4);
    v6[0] = Syn_type(Symbol, "*");
    v6[1] = Syn_type(Symbol, "F");
    v6[2] = Syn_type(Operation, "*", GEQ);
    v6[3] = Syn_type(Symbol, "T'");

    vector<Syn_type> v7(4);
    v7[0] = Syn_type(Symbol, "/");
    v7[1] = Syn_type(Symbol, "F");
    v7[2] = Syn_type(Operation, "/", GEQ);
    v7[3] = Syn_type(Symbol, "T'");

    vector<Syn_type> v8(4);
    v8[0] = Syn_type(Symbol, "%");
    v8[1] = Syn_type(Symbol, "F");
    v8[2] = Syn_type(Operation, "%", GEQ);
    v8[3] = Syn_type(Symbol, "T'");

    unordered_map<string, vector<Syn_type>> m4;
    m4["+"] = v4;
    m4["-"] = v4;
    m4["*"] = v6;
    m4["/"] = v7;
    m4["%"] = v8;
    m4[")"] = v4;
    m4["#"] = v4;

    analysis_map["T'"] = m4;

    // row F
    vector<Syn_type> v9(2);
    v9[0] = Syn_type(Symbol, "N");
    v9[1] = Syn_type(Symbol, "F'");

    unordered_map<string, vector<Syn_type>> m5;
    m5["("] = v9;
    m5["+"] = v9;
    m5["-"] = v9;
    m5["i"] = v9;

    analysis_map["F"] = m5;

    // row F'
    vector<Syn_type> v10(3);
    v10[0] = Syn_type(Symbol, "^");
    v10[1] = Syn_type(Symbol, "F");
    v10[2] = Syn_type(Operation, "^", GEQ);

    unordered_map<string, vector<Syn_type>> m6;
    m6["+"] = v4;
    m6["-"] = v4;
    m6["*"] = v4;
    m6["/"] = v4;
    m6["%"] = v4;
    m6["^"] = v10;
    m6[")"] = v4;
    m6["#"] = v4;

    analysis_map["F'"] = m6;

    // row N
    vector<Syn_type> v11(3);
    v11[0] = Syn_type(Symbol, "(");
    v11[1] = Syn_type(Symbol, "E");
    v11[2] = Syn_type(Symbol, ")");

    vector<Syn_type> v12(3);
    v12[0] = Syn_type(Symbol, "+");
    v12[1] = Syn_type(Symbol, "N");
    v12[2] = Syn_type(Operation, "+'", GEQ);

    vector<Syn_type> v13(3);
    v13[0] = Syn_type(Symbol, "-");
    v13[1] = Syn_type(Symbol, "N");
    v13[2] = Syn_type(Operation, "-'", GEQ);

    vector<Syn_type> v14(2);
    v14[0] = Syn_type(Symbol, "i");
    v14[1] = Syn_type(Operation, "i", PUSH);

    unordered_map<string, vector<Syn_type>> m7;
    m7["("] = v11;
    m7["+"] = v12;
    m7["-"] = v13;
    m7["i"] = v14;

    analysis_map["N"] = m7;
}

void DigitExpressionParser_LL1::printQT() {
    for (int i = 0; i < QT.size(); i++) {
        cout << "(" << QT[i].operation << ", " << QT[i].first << ", " << QT[i].second << ", " << QT[i].result << ")" << endl;
    }
}

DigitExpressionParser_LL1::DigitExpressionParser_LL1() { initialMaps(); }

bool DigitExpressionParser_LL1::parse(string file_name) {
    if (!_init(file_name)) {
        cerr << "Error: source string empty or wrong token" << endl;
        return false;
    }

    int times = 1;

    string curCharacter = characters.front();
    characters.pop();
    while (true) {
        if (SYN.empty()) {
            cout << "Empty Stack" << endl;
            exit(-1);
        }
        Syn_type curSyn = SYN.top();
        SYN.pop();
        // cout << curSyn.character << " " << curCharacter << endl;

        if (curSyn.character == "#" && curCharacter == "#") {
            cout << "Accepted" << endl;
            return true;
        }

        if (curSyn.syn_kind == Symbol) {
            string curV = curSyn.character;
            string _curCharacter = curCharacter;
            if (is_i(curCharacter)) _curCharacter = "i";
            if (find(V.begin(), V.end(), curV) != V.end()) {
                if (analysis_map[curV].find(_curCharacter) == analysis_map[curV].end()) {
                    if (is_i(curCharacter))
                        cout << "Missing operator" << endl;
                    else
                        cout << "Missing operand" << endl;
                    exit(-1);
                }
                vector<Syn_type> sec = analysis_map[curV][_curCharacter];
                push(SYN, analysis_map[curV][_curCharacter], curCharacter);
                // cout << analysis_map[curV][curCharacter] << endl;
            } else {
                if (curV == curCharacter) {
                    curCharacter = characters.front();
                    characters.pop();
                } else {
                    if (curV == ")")
                        cout << "Missing right parenthesis" << endl;
                    else
                        cout << "Missing left parenthesis" << endl;
                    exit(-1);
                }
            }
        } else {
            if (curSyn.ope_kind == PUSH) {
                SEM.push(curSyn.character);
            } else {
                if (curSyn.character == "+'" || curSyn.character == "-'") {
                    string first = SEM.top();
                    SEM.pop();
                    string result = "t" + to_string(times++);
                    SEM.push(result);
                    QT.push_back(quat(curSyn.character.substr(0, 1), first, "_", result));
                } else {
                    string second = SEM.top();
                    SEM.pop();
                    string first = SEM.top();
                    SEM.pop();
                    string result = "t" + to_string(times++);
                    SEM.push(result);
                    QT.push_back(quat(curSyn.character, first, second, result));
                }
            }
        }
    }
    return false;
}