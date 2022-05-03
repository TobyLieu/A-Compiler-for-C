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
void DigitExpressionParser_LL1::push(stack<string> &s, string &ss){
    for (int i = ss.size() - 1; i >= 0; i--) {
        s.push(ss.substr(i, 1));
    }
}

bool DigitExpressionParser_LL1::_init(string file_name) {
    characters = lex2Str(file_name);
    entered.push("#");
    entered.push("E");
    return true;
}

void DigitExpressionParser_LL1::initialMaps() {
    const int m[7][10] = {
        {0, 0, 0, -1, -1, -1, -1, -1, 0, -1},
        {-1, 1, 2, -1, -1, -1, -1, 3, -1, 3},
        {4, 4, 4, -1, -1, -1, -1, -1, 4, -1},
        {-1, 8, 8, 5, 6, 7, -1, 8, -1, 8},
        {9, 9, 9, -1, -1, -1, -1, -1, 9, -1},
        {-1, 11, 11, 11, 11, 11, 10, 11, -1, 11},
        {12, 14, 15, -1, -1, -1, -1, -1, 13, -1}
    };
    for (int i = 0; i < 7; i++) {
        unordered_map<string, string> tmp;
        for (int j = 0; j < 10; j++) {
            if (m[i][j] != -1) {
                tmp[T[j]] = producers[m[i][j]].second;
            }
        }
        analysis_map[V[i]] = tmp;
    }
}

void DigitExpressionParser_LL1::printProducer(int id) { cout << producers[id].first << "->" << producers[id].second << endl; }

DigitExpressionParser_LL1::DigitExpressionParser_LL1() { initialMaps(); }

bool DigitExpressionParser_LL1::parse(string file_name) {
    if (!_init(file_name)) {
        cerr << "Error: source string empty or wrong token" << endl;
        return false;
    }

    string curCharacter = characters.front();
    characters.pop();
    while (true) {
        if(entered.empty()){
            cout << "Empty Stack" << endl;
            return false;
        }
        string curV = entered.top();
        entered.pop();
        cout << curV << " " << curCharacter << endl;

        if (curV == "#" && curCharacter == "#") {
            cout << "Accepted" << endl;
            return true;
        }

        if (find(V.begin(), V.end(), curV) != V.end()) {
            if(analysis_map[curV].find(curCharacter) == analysis_map[curV].end()){
                if (curV == "f") cout << "Missing operator" << endl;
                else cout << "Missing operand" << endl;
                return false;
            }
            string sec = analysis_map[curV][curCharacter];
            push(entered, analysis_map[curV][curCharacter]);
            cout << analysis_map[curV][curCharacter] << endl;
        } else {
            if (curV == curCharacter) {
                curCharacter = characters.front();
                characters.pop();
            }else{
                if (curV == ")") cout << "Missing right parenthesis" << endl;
                else cout << "Missing left parenthesis" << endl;
                return false;
            }
        }
    }
    return false;
}