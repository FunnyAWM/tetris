#include "game.h"
#include "func.h"
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::getline;

int main() {
    clock_t start,end;
    start=clock();
    gameInit();
    end=clock();
    auto time=double(end-start)/CLOCKS_PER_SEC;
    cout << endl << time << " secs in total.";
    getchar();
    closeHandle();
}