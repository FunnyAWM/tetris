#include "game.h"
#include "core.h"
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::getline;

int main() {
    int x;
    int y;
    clock_t start, end;
    start = clock();
    gameInit();
    generateBlock();
    displayBlock(20,1,0x0d);
    end = clock();
    getchar();
    deleteBlock(20,1);
    auto time = double(end - start) / CLOCKS_PER_SEC;
    setPosition(0, 25);
    cout << endl << time << " secs in total.";
    getchar();
    closeHandle();
}