#include "game.h"
#include "core.h"
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::getline;

int main() {
    clock_t start, end;
    start = clock();
    gameInit();
    end = clock();
    moveBlock();
    auto time = double(end - start) / CLOCKS_PER_SEC;
    setPosition(0, 25);
    cout << endl << time << " secs in total.";
    getchar();
    closeHandle();
}