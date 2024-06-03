#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

class Block {
private:
    int blockIndex;
    int blockStatus;
    int color;
    int x;
    int y;
public:

    Block();

    void displaySelf();

    void deleteSelf();

    int Crash();

    void moveLeft();

    void moveRight();

    void rotate();

    inline int moveDown();

    void moveBottom();

    void saveBlock();

    void refresh();

    ~Block() = default;
};

void renderWindow(int, int);

void gameInit();

void displayUI();

void displayScore(int);

void pause();

void update();

void fullDetect();

void fullDown(int);

void over();

void finish();

void again();

void gameClose();

void printStart(int, int);

void clearStart(int, int);

void start();

void readHighest();

inline void clearArea();

#endif //TETRIS_GAME_H
