#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

struct block {
    int blockIndex;
    int blockStatus;
    int color;
    int x;
    int y;
};

int crash(block);

void copyBlock(block *, block *);

void renderWindow(int, int);

void gameInit();

void displayUI();

void displayScore(int);

void generateBlock();

inline void displayBlock(block);

inline void deleteBlock(block);

void moveLeft();

void moveRight();

void rotate();

inline int moveDown();

void pause();

void moveBottom();

void saveBlock();

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
