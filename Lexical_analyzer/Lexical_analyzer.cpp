#include "Lexical_analyzer.h"
using namespace std;

vector<char> symbol = {'+', '-', '*', '/', '%', '!', '=', '>', '<', '&', '|', '^', '~', '?', '{', '}', '[', ']', '(', ')', ',', ';', '\\'};

unordered_map<string, int> _KT = {
    {"auto", 4},       //声明自动变量
    {"short", 5},      //声明短整型变量或函数
    {"int", 6},        //声明整型变量或函数
    {"long", 7},       //声明长整型变量或函数
    {"float", 8},      //声明浮点型变量或函数
    {"double", 9},     //声明双精度变量或函数
    {"char", 10},      //声明字符型变量或函数
    {"struct", 11},    //声明结构体变量或函数
    {"union", 12},     //声明共用数据类型
    {"enum", 13},      //声明枚举类型
    {"typedef", 14},   //用以给数据类型取别名
    {"const", 15},     //声明只读变量
    {"unsigned", 16},  //声明无符号类型变量或函数
    {"signed", 17},    //声明有符号类型变量或函数
    {"extern", 18},    //声明变量是在其他文件正声明
    {"register", 19},  //声明寄存器变量
    {"static", 20},    //声明静态变量
    {"volatile", 21},  //说明变量在程序执行中可被隐含地改变
    {"void", 22},      //声明函数无返回值或无参数，声明无类型指针
    {"if", 23},        //条件语句
    {"else", 24},      //条件语句否定分支（与 if 连用）
    {"switch", 25},    //用于开关语句
    {"case", 26},      //开关语句分支
    {"for", 27},       //一种循环语句
    {"do", 28},        //循环语句的循环体
    {"while", 29},     //循环语句的循环条件
    {"goto", 30},      //无条件跳转语句
    {"continue", 31},  //结束当前循环，开始下一轮循环
    {"break", 32},     //跳出当前循环
    {"default", 33},   //开关语句中的“其他”分支
    {"sizeof", 34},    //计算数据类型长度
    {"return", 35},    //子程序返回语句（可以带参数，也可不带参数）循环条件}
    {"main", 36}       //并不是关键字，但是作为主函数的名称，也放在这个表中
};
unordered_map<string, int> _PT = {
    {"+", 36},    //把两个操作数相加
    {"-", 37},    //从第一个操作数中减去第二个操作数
    {"*", 38},    //把两个操作数相乘 或者 指向一个变量
    {"/", 39},    //分子除以分母
    {"%", 40},    //取模运算符，整除后的余数
    {"++", 41},   //自增运算符，整数值增加1
    {"--", 42},   //自减运算符，整数值减少1
    {"==", 43},   //检查两个操作数的值是否相等，如果相等则条件为真
    {"!=", 44},   //检查两个操作数的值是否相等，如果不相等则条件为真
    {">", 45},    //检查左操作数的值是否大于右操作数的值，如果是则条件为真
    {"<", 46},    //检查左操作数的值是否小于右操作数的值，如果是则条件为真
    {">=", 47},   //检查左操作数的值是否大于或等于右操作数的值，如果是则条件为真
    {"<=", 48},   //检查左操作数的值是否小于或等于右操作数的值，如果是则条件为真
    {"&&", 49},   //称为逻辑与运算符。如果两个操作数都非零，则条件为真
    {"||", 50},   //称为逻辑或运算符。如果两个操作数中有任意一个非零，则条件为真
    {"!", 51},    //称为逻辑非运算符。用来逆转操作数的逻辑状态。如果条件为真则逻辑非运算符将使其为假
    {"&", 52},    //按位与操作，按二进制位进行"与"运算 或者 返回变量的地址
    {"|", 53},    //按位或运算符，按二进制位进行"或"运算
    {"^", 54},    //异或运算符，按二进制位进行"异或"运算
    {"~", 55},    //取反运算符，按二进制位进行"取反"运算
    {"<<", 56},   //二进制左移
    {">>", 57},   //二进制右移
    {"=", 58},    //简单的赋值运算符，把右边操作数的值赋给左边操作数
    {"+=", 59},   //加且赋值运算符，把右边操作数加上左边操作数的结果赋值给左边操作数
    {"-=", 60},   //减且赋值运算符，把左边操作数减去右边操作数的结果赋值给左边操作数
    {"*=", 61},   //乘且赋值运算符，把右边操作数乘以左边操作数的结果赋值给左边操作数
    {"/=", 62},   //除且赋值运算符，把左边操作数除以右边操作数的结果赋值给左边操作数
    {"%=", 63},   //求模且赋值运算符，求两个操作数的模赋值给左边操作数
    {"<<=", 64},  //左移且赋值运算符
    {">>=", 65},  //右移且赋值运算符
    {"&=", 66},   //按位与且赋值运算符
    {"^=", 67},   //按位异或且赋值运算符
    {"|=", 68},   //按位或且赋值运算符
    {"?", 71},    //条件表达式
    {"{", 72},    //左大括号
    {"}", 73},    //右大括号
    {"[", 74},    //左中括号
    {"]", 75},    //右中括号
    {"(", 76},    //左小括号
    {")", 77},    //右小括号
    {",", 78},    //逗号
    {";", 79},    //分号
    {"\\", 80}    //反斜杠
};

Lexical_analyzer::Lexical_analyzer() {
    initialize_code_table();
    initialize_transition_table();
}

void Lexical_analyzer::initialize_code_table() {
    KT = _KT;
    PT = _PT;
}
void Lexical_analyzer::initialize_transition_table() {
    // initialize state 1
    unordered_map<char, int> tmp;
    tmp[' '] = 1;
    tmp['\n'] = 1;
    tmp['\t'] = 1;
    for (int i = 'A'; i <= 'Z'; i++) {
        tmp[i] = 2;
    }
    for (int i = 'a'; i <= 'z'; i++) {
        tmp[i] = 2;
    }
    for (int i = '0'; i <= '9'; i++) {
        tmp[i] = 3;
    }
    tmp['\''] = 10;
    tmp['\"'] = 13;
    for (int i = 0; i < symbol.size(); i++) {
        tmp[symbol[i]] = 16;
    }
    transition_table[1] = tmp;

    // initialize_state_2
    tmp.clear();
    for (int i = 'A'; i <= 'Z'; i++) {
        tmp[i] = 2;
    }
    for (int i = 'a'; i <= 'z'; i++) {
        tmp[i] = 2;
    }
    for (int i = '0'; i <= '9'; i++) {
        tmp[i] = 2;
    }
    transition_table[2] = tmp;

    // initialize_state_3
    tmp.clear();
    for (int i = '0'; i <= '9'; i++) {
        tmp[i] = 3;
    }
    tmp['.'] = 4;
    tmp['e'] = 6;
    transition_table[3] = tmp;

    // initialize_state_4
    tmp.clear();
    for (int i = '0'; i <= '9'; i++) {
        tmp[i] = 5;
    }
    transition_table[4] = tmp;

    // initialize_state_5
    tmp.clear();
    for (int i = '0'; i <= '9'; i++) {
        tmp[i] = 5;
    }
    tmp['e'] = 6;
    transition_table[5] = tmp;

    // initialize_state_6
    tmp.clear();
    for (int i = '0'; i <= '9'; i++) {
        tmp[i] = 7;
    }
    tmp['-'] = 8;
    transition_table[6] = tmp;

    // initialize_state_7
    tmp.clear();
    for (int i = '0'; i <= '9'; i++) {
        tmp[i] = 7;
    }
    transition_table[7] = tmp;

    // initialize_state_8
    tmp.clear();
    for (int i = '0'; i <= '9'; i++) {
        tmp[i] = 9;
    }
    transition_table[8] = tmp;

    // initialize_state_9
    tmp.clear();
    for (int i = '0'; i <= '9'; i++) {
        tmp[i] = 9;
    }
    transition_table[9] = tmp;

    // initialize_state_10
    tmp.clear();
    for (int i = 0; i <= 127; i++) {
        tmp[i] = 11;
    }
    transition_table[10] = tmp;

    // initialize_state_11
    tmp.clear();
    tmp['\''] = 12;
    transition_table[11] = tmp;

    // initialize_state_12
    tmp.clear();
    transition_table[12] = tmp;

    // initialize_state_13
    tmp.clear();
    for (int i = 0; i <= 127; i++) {
        tmp[i] = 14;
    }
    transition_table[13] = tmp;

    // initialize_state_14
    tmp.clear();
    for (int i = 0; i <= 127; i++) {
        tmp[i] = 14;
    }
    tmp['\"'] = 15;
    transition_table[14] = tmp;

    // initialize_state_15
    tmp.clear();
    transition_table[15] = tmp;

    // initialize_state_16
    tmp.clear();
    for (int i = 0; i < symbol.size(); i++) {
        tmp[i] = 16;
    }
    transition_table[16] = tmp;
}

int Lexical_analyzer::state_change(int state, char ch) {
    unordered_map<char, int> tmp = transition_table[state];
    if (tmp.find(ch) == tmp.end()) return 0;
    return tmp[ch];
}

int Lexical_analyzer::state_to_code(int state_before, string token) {
    int ret;
    switch (state_before) {
        case 2:
            if (KT.find(token) == KT.end()) {
                iT[token] = 0;
                return 0;
            } else {
                return KT[token];
            }
        case 3:
            return 3;
        case 5:
            return 3;
        case 7:
            return 3;
        case 9:
            return 3;
        case 12:
            cT[token] = 1;
            return 1;
        case 15:
            sT[token] = 2;
            return 2;
        case 16:
            if (PT.find(token) == PT.end()) {
                cout << token << " "
                     << "symbol error!" << endl;
                exit(1);
            }
            return PT[token];
    }
    return -1;
}