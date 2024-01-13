#include "game.h"
#include <cstring>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
block CURRENT, NEXT;


int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "-clear") == 0) {
        cout << "This is a developer only feature.\nWould you continue?[y/N]";
        char ch;
        cin >> ch;
        if (ch == 'y' || ch == 'Y') {
            std::ofstream fout;
            fout.open("highest.bin", std::ios_base::trunc | std::ios_base::binary);
            if (!fout.is_open()) {
                std::cerr << "Can't open the file.\n";
                exit(EXIT_FAILURE);
            }
            cout << "highest.bin cleaned.\n";
            cout << "Enter to close the program.\n";
            getchar();
            getchar();
            fout.close();
            return 0;
        } else {
            return 0;
        }
    }
    gameInit();
    gameClose();
    return 0;
}