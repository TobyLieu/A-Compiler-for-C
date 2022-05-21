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
};

class DigitExpressionParser_LL1 {
   private:
    stack<string> entered;
    queue<string> characters;
    unordered_map<string, unordered_map<string, string>> analysis_map;
    vector<string> T{"(", "+", "-", "*", "/", "%", "^", ")", "i", "#"};
    vector<string> V{"E", "e", "T", "t", "F", "f", "N"};
    vector<pair<string, string>> producers = {{"E", "Te"}, {"e", "+Te"}, {"e", "-Te"}, {"e", ""}, {"T", "Ft"}, {"t", "*Ft"}, {"t", "/Ft"}, {"t", "%Ft"}, {"t", ""}, {"F", "Nf"}, {"f", "^F"}, {"f", ""}, {"N", "(E)"}, {"N", "i"}, {"N", "+i"}, {"N", "-i"}};

    queue<string> lex2Str(string file_name);
    //  function overload for different container to pop numofEle
    void push(stack<string>& s, string& ss);

    // initialize parser
    bool _init(string file_name);

    // initialize analysis table
    void initialMaps();

    // print action
    void printProducer(int id);

   public:
    DigitExpressionParser_LL1();
    // parse
    bool parse(string file_name);
};