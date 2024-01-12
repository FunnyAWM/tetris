#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::getline;

void renderWindow(int, int);

void gameInit();

void displayUI();

void displayLevel(int);

void generateBlock(int, int, int);

void deleteBlock(int, int);

void moveBlock();

void moveLeft();

void moveRight();

void rotate();

void moveDown();

void pause();

void moveBottom();

#endif //TETRIS_GAME_H
