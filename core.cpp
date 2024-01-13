#include "core.h"

HANDLE handle;

//ϵͳ����ģ��

void initHandle() {
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
}

void setColor(int color) {
    SetConsoleTextAttribute(handle, color);
}

void setCursorVisibility(int flag) {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = flag;
    cursorInfo.dwSize = 100;
    SetConsoleCursorInfo(handle, &cursorInfo);
}

void setPosition(int x, int y) {
    COORD position = {static_cast<SHORT>(x * 2), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(handle, position);
}

void setTitle(const std::string &title) {
    SetConsoleTitle(title.c_str());
}

void closeHandle() {
    CloseHandle(handle);
}