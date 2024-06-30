#include "game.hpp"
#include <cstring>
#include <fstream>
#include <conio.h>

/*#pragma comment(lib, "winmm")*/

using std::cout;
using std::cin;
using std::endl;

//这个代码可能有亿点点bug
//不过相信我，没逝的
int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "-clear") == 0) {
        cout << "This will clean the highest score record.\nWould you continue?[y/N]";
        switch (_getch()) {
            case 'y':
            case 'Y':
                std::ofstream fout;
                fout.open("highest.bin", std::ios_base::trunc | std::ios_base::binary);
                if (!fout.is_open()) {
                    std::cerr << "Can't open the file.\n";
                    exit(EXIT_FAILURE);
                }
                cout << "\nhighest.bin cleaned.\n";
                cout << "Enter to close the program.\n";
                getchar();
                getchar();
                fout.close();
                return 0;
        }
    }
    gameInit();
    gameClose();
    return 0;
}