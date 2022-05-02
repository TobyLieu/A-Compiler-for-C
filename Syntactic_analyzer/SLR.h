#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

typedef int State;

enum ActionKind { Error, Shift, Reduce, Accpet };
struct Action {
    ActionKind kind;
    int id;
};  // id is for reduce and shift

typedef unordered_map<string, Action> ActionMap;
typedef unordered_map<string, State> GotoMap;

class DigitExpressionParser_SLR {
   private:
    stack<string> entered;
    queue<string> characters;
    vector<string> T{"(", ")", "+", "-", "*", "/", "%", "^", "i", ""};
    vector<string> V{"E", "T", "F", "N"};
    stack<State> states;
    vector<ActionMap> am;
    vector<GotoMap> gm;
    vector<pair<string, string>> producers = {
        {"E'", "E"}, 
        {"E", "E+T"}, 
        {"E", "E-T"}, 
        {"E", "T"}, 
        {"T", "T*F"}, 
        {"T", "T/F"}, 
        {"T", "T%F"}, 
        {"T", "F"}, 
        {"F", "N^F"}, 
        {"F", "N"}, 
        {"N", "(E)"}, 
        {"N", "i"}, 
        {"N", "+i"}, 
        {"N", "-i"}
    };

    queue<string> lex2Str(string file_name);
    //  function overload for different container to pop numofEle
    void pop(queue<string> &q, int num);
    void pop(stack<string> &s, int num);
    void pop(stack<State> &s, int num);

    // parse to action
    Action parse2Action(string s);

    // initialize parser
    bool _init(string file_name);

    // initialize am, gm
    void initialMaps();

    // print action
    void printProducer(int id);

   public:
    DigitExpressionParser_SLR();
    // parse
    bool parse(string file_name);
};