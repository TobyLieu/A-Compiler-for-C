#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

class Lexical_analyzer {
   private:
    unordered_map<string, int> iT;                                  // 标识符
    unordered_map<string, int> cT;                                  // 字符
    unordered_map<string, int> sT;                                  // 字符串
    unordered_map<string, int> CT;                                  // 常数
    unordered_map<string, int> KT;                                  // 关键字
    unordered_map<string, int> PT;                                  // 界符
    unordered_map<int, unordered_map<char, int>> transition_table;  // 状态转换表
    vector<pair<string, int>> tokens;                               // token列表

   public:
    Lexical_analyzer();                  // 构造函数
    void initialize_code_table();        // 初始化类别码表
    void initialize_transition_table();  // 初始化状态转换表
    int state_change(int, char);         // 状态转换
    int state_to_code(int, string);      // 由token得到类别码
    void parse(int);                     // 将类别码传到语法分析器（本次实验中用不到）
    void store(string, int);             // 将token存入列表
};