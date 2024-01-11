#ifndef TETRIS_FUNC_H
#define TETRIS_FUNC_H

#include <windows.h>
#include <iostream>
#include <string>
#include <ctime>

using std::string;

void initHandle();

void setColor(int);

void setCursorVisibility(int);

void setPosition(int, int);

void setWindowSize(int, int);

void setTitle(const string &);

void closeHandle();

#endif //TETRIS_FUNC_H
