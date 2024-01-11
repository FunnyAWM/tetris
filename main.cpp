#include "func.h"
#include <iostream>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::getline;

int main() {
    initHandle();
    setPosition(15,15);
    setWindowSize(600,800);
    string str;
    getline(cin,str);
    setColor(0x1c);
    setTitle("Tetris Game");
    cout << str << endl;
    getchar();
    closeHandle();
}