#include "game.h"
#include "func.h"
#include "data.h"

void renderWindow(int x, int y) {
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 26; j++) {
            if (windowShape[i][j] == 1) {
                setColor(0xc0);
                setPosition(j + x, i + y);
                cout << "  ";
            }
        }
    }
}

void gameInit() {
    initHandle();
    setCursorVisibility(0);
    setTitle("Tetris");
    renderWindow(15, 0);
}