#include "game.h"
#include "core.h"
#include <ctime>
#include <mutex>

std::mutex mtx;

using std::cout;
using std::cin;
using std::endl;
using std::getline;
int main() {
    int x;
    int y;
    HANDLE keydetection;
    keydetection = CreateThread(nullptr,0,moveBlock,nullptr,0,nullptr);
    clock_t start, end;
    start = clock();
    gameInit();
    generateBlock();
    for(int i=1;i<23;i++){
        mtx.lock();
        x=20;
        y=i;
        displayBlock(x,y,0x0c);
        Sleep(500);
        deleteBlock(x,y);
        mtx.unlock();
    }
    end = clock();
    getchar();
    auto time = double(end - start) / CLOCKS_PER_SEC;
    setPosition(0, 25);
    cout << endl << time << " secs in total.";
    getchar();
    CloseHandle(keydetection);
    closeHandle();
}