#ifndef TETRIS_CORE_H
#define TETRIS_CORE_H

#include <windows.h>
#include <string>

using std::string;

void initHandle();

void setColor(int);

void setCursorVisibility(int);

void setPosition(int, int);

void setWindowSize(int, int);

void setTitle(const string &);

void closeHandle();

#endif //TETRIS_CORE_H
