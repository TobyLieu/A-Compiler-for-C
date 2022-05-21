#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

struct quat {
    string operation;
    string first;
    string second;
    string result;
    quat(string _operation, string _first, string _second, string _result) {
        operation = _operation;
        first = _first;
        second = _second;
        result = _result;
    }
};

enum SynKind { Symbol, Operation };
enum OperationKind { PUSH, GEQ };
struct Syn_type {
    SynKind syn_kind;
    string character;
    OperationKind ope_kind;
    Syn_type(SynKind _syn_kind = Symbol, string _character = "", OperationKind _ope_kind = PUSH) {
        syn_kind = _syn_kind;
        character = _character;
        ope_kind = _ope_kind;
    }
};

class DigitExpressionParser_LL1 {
   private:
    stack<Syn_type> SYN;
    queue<string> characters;
    stack<string> SEM;
    vector<quat> QT;
    unordered_map<string, unordered_map<string, vector<Syn_type>>> analysis_map;
    vector<string> T{"(", "+", "-", "*", "/", "%", "^", ")", "i", "#"};
    vector<string> V{"E", "E'", "T", "T'", "F", "F'", "N"};
    // vector<pair<string, string>> producers = {{"E", "Te"}, {"e", "+T{+}e"}, {"e", "-T{-}e"}, {"e", ""}, {"T", "Ft"}, {"t", "*F{*}t"}, {"t", "/F{/}t"}, {"t", "%F{%}t"}, {"t", ""}, {"F", "Nf"}, {"f", "^F{^}"}, {"f", ""}, {"N", "(E)"}, {"N", "i{i}"}, {"N", "+N{+'}"}, {"N", "-N{-'}"}};

    queue<string> lex2Str(string file_name);
    //  function overload for different container to pop numofEle
    void push(stack<Syn_type> &SYN, vector<Syn_type> list, string &curCharacter);

    // s is i or not
    bool is_i(string &s);

    // initialize parser
    bool _init(string file_name);

    // initialize analysis table
    void initialMaps();

   public:
    DigitExpressionParser_LL1();
    // parse
    bool parse(string file_name);
    // print QT
    void printQT();
};