#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::getline;

struct block{
    int blockIndex;
    int blockStatus;
    int color;
    int x;
    int y;
};

bool crash(block BLOCK);

void copyBlock(block*,block*);

void renderWindow(int, int);

void gameInit();

void displayUI();

void displayLevel(int);

void generateBlock();

void displayBlock(block);

void deleteBlock(block);

void moveBlock();

void moveLeft();

void moveRight();

void rotate();

void moveDown();

void pause();

void moveBottom();

void saveBlock();

void gameClose();

#endif //TETRIS_GAME_H
