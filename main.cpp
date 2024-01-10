#include <windows.h>
#include <iostream>
#include <ctime>

using namespace std;

int main() {
    clock_t timeStart=clock();
    SetConsoleTitle("Hello");
    HANDLE consoleOutput;
    consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD start = {5, 15};
    SetConsoleCursorPosition(consoleOutput, start);
    SetConsoleTextAttribute(consoleOutput,0x41);
    cout << "Hello";
    SetConsoleTextAttribute(consoleOutput, 0x42);
    cout << " World\n";
    clock_t timeEnd=clock();
    SetConsoleTextAttribute(consoleOutput,0x0F);
    cout << double(timeEnd-timeStart)/CLOCKS_PER_SEC << " secs used in total.";
    CloseHandle(consoleOutput);
    getchar();
    return 0;
}