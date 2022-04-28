#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

typedef int State;

struct Action {
    ActionKind kind;
    int id;
};  // id is for reduce and shift
enum ActionKind { Error, Shift, Reduce, Accpet };

typedef unordered_map<string, Action> ActionMap;
typedef unordered_map<string, State> GotoMap;

const pair<string, string> producers[] = {{"E'", "E"}, E->E + T E->E - T E->T T->T *F T->T / F T->T % F T->F F->N ^ F F->N N->(E)N->i N->+ i N->- i};

class DigitExpressionParser {
   private:
    stack<string> entered;
    queue<string> characters;
    unordered_set<string> T{"(", ")", "-", "+", "*", "/", "num", "$"};
    unordered_set<string> V{"E", "T", "F"};
    stack<State> states;
    vector<ActionMap> am;
    vector<GotoMap> gm;

    vector<string> lex2Str(string sourceStr);
    //  function overload for different container to pop numofEle
    void pop(queue<string> &q, int num);
    void pop(stack<string> &s, int num);
    void pop(stack<State> &s, int num);

    // initialize parser
    bool _init(string sourceString);

    // initialize am, gm
    void initialMaps(vector<ActionMap> &am, vector<GotoMap> &gm);

   public:
    DigitExpressionParser() { initialMaps(am, gm); }
    // parse
    bool parse(string sourseStr) {
        if (!_init(sourseStr)) {
            cerr << "Error:source string empty or wrong token" << endl;
            return false;
        }

        while (true) {
            State curState = states.top();
            string curCharacter = characters.front();

            auto &action = am[curState][curCharacter];

            switch (action.kind) {
                case Shift:
                    states.push(action.id);
                    entered.push(curCharacter);
                    characters.pop();
                    break;

                case Reduce: {
                    // use producer[id] to reduce
                    printProducer(action.id);
                    auto producer = producers[action.id];
                    int popNum = producer.second == "num" ? 1 : producer.second.size();
                    pop(states, popNum);
                    pop(entered, popNum);
                    entered.push(producer.first);

                    states.push(gm[states.top()][producer.first]);
                } break;

                case Error:
                    cerr << "Error while parsing" << endl;
                    return false;

                case Accpet:
                    cout << "Accepted" << endl;
                    return true;
            }
        }
    }
};