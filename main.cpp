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
    for(int i=1;i<23;i++){
        x=20;
        y=i;
        displayBlock(x,y,0x0c);
        Sleep(500);
        deleteBlock(x,y);
    }
    end = clock();
    getchar();
    auto time = double(end - start) / CLOCKS_PER_SEC;
    setPosition(0, 25);
    cout << endl << time << " secs in total.";
    getchar();
    closeHandle();
}