#include "func.h"
#include <iostream>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::getline;

int main() {
    clock_t start,end;
    start=clock();
    initHandle();
    setPosition(15,15);
    setWindowSize(600,800);
    setColor(0x1c);
    setTitle("Tetris Game");
    cout << "Hello world!\n";
    end=clock();
    double timeUsed=(double)(end-start)/CLOCKS_PER_SEC;
    cout << timeUsed << " secs used in total.\n";
    getchar();
    closeHandle();
}