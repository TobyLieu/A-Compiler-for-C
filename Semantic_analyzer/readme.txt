环境：Ubuntu 20.04 Windows子系统

g++ SLR.cpp main_SLR.cpp Lexical_analyzer.cpp -o main_SLR对SLR分析器进行编译
./main_SLR运行

g++ LL1.cpp main_LL1.cpp Lexical_analyzer.cpp -o main_LL1对LL(1)分析器进行编译
./main_LL1运行

text.txt为输入文本，可在其中对输入进行修改

输出在终端