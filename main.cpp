#include "game.h"
#include "core.h"
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
block CURRENT, NEXT;

int main() {
    clock_t start, end;
    start = clock();
    gameInit();
    end = clock();
    displayBlock(CURRENT);
    moveBlock();
    gameClose();
}