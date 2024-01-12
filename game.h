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

void displayBlock(int,int,int);

#endif //TETRIS_GAME_H
