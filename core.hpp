#ifndef TETRIS_CORE_HPP
#define TETRIS_CORE_HPP

#include <windows.h>
#include <string>

using std::string;

void initHandle();

void setColor(int);

void setCursorVisibility(int);

void setPosition(int, int);

void setTitle(const string &);

void closeHandle();

#endif //TETRIS_CORE_HPP
