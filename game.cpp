#include <conio.h>
#include <fstream>
#include <random>
#include "game.h"
#include "core.h"
#include "data.h"

//游戏窗口渲染
int level = 1;
int score = 0;
int highest = 0;

extern block CURRENT, NEXT;

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
    std::ifstream fin;
    fin.open("highest.bin", std::ios_base::binary);
    if (!fin.is_open()) {
        std::ofstream fout;
        fout.open("highest.bin", std::ios_base::binary | std::ios_base::trunc);
        if (!fout.is_open()) {
            std::cerr << "Failed to create file.";
            exit(EXIT_FAILURE);
        }
        fout << "0" << endl;
        fout.close();
        fin.open("highest.bin", std::ios_base::binary);
        fin >> highest;
        fin.close();
    }
    fin >> highest;
    fin.close();
    setTitle("Tetris");
    renderWindow(15, 0);
    displayUI();
    displayLevel(0);
    generateBlock();
    copyBlock(&CURRENT, &NEXT);
    generateBlock();
    displayBlock(NEXT);
}

void displayUI() {
    setColor(0x0a);
    setPosition(31, 9);
    cout << "操作说明：";
    setColor(0x0b);
    setPosition(32, 11);
    cout << "按 A 左移\n";
    setPosition(32, 12);
    cout << "按 D 右移\n";
    setPosition(32, 13);
    cout << "按 W 旋转\n";
    setPosition(32, 14);
    cout << "按 S 加速下落\n";
    setPosition(32, 15);
    cout << "按 空格 暂停\n";
    setPosition(32, 16);
    cout << "按 回车 直接下落\n";
}

void displayLevel(int num) {
    switch (num) {
        case 0:
            break;
        case 1:
            score += 10;
            break;
        case 2:
            score += 30;
            break;
        case 3:
            score += 50;
            break;
        case 4:
            score += 80;
            break;
        default:
            break;
    }
    setColor(0x09);
    setPosition(6, 3);
    cout << "分数：" << score << endl;
    setPosition(6, 4);
    cout << "历史最高分：" << highest << endl;
    setPosition(6, 5);
    cout << "等级：" << level << endl;
}

void generateBlock() {
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<> index(0, 6);
    std::uniform_int_distribution<> status(0, 3);
    std::uniform_int_distribution<> color(0x00, 0x10);
    NEXT.x = 33;
    NEXT.y = 3;
    NEXT.blockIndex = index(gen);
    NEXT.blockStatus = status(gen);
    NEXT.color = color(gen);
}

void displayBlock(block BLOCK) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blockShape[BLOCK.blockIndex][BLOCK.blockStatus][i][j] == 1) {
                setColor(BLOCK.color);
                setPosition(BLOCK.x + j, BLOCK.y + i);
                cout << "■";
            } else {
                setColor(0);
                cout << "  ";
            }
        }
        cout << endl;
    }
}

void deleteBlock(block BLOCK) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blockShape[BLOCK.blockIndex][BLOCK.blockStatus][i][j] == 1) {
                setPosition(BLOCK.x + j, BLOCK.y + i);
                cout << "  ";
            }
        }
    }
}

void moveBlock() {
    for (;;) {
        if (kbhit()) {
            switch (getch()) {
                case 'W':
                case 'w':
                case 72:
                    rotate();
                    break;
                case 'A':
                case 'a':
                case 75:
                    moveLeft();
                    break;
                case 'D':
                case 'd':
                case 77:
                    moveRight();
                    break;
                case 'S':
                case 's':
                case 80:
                    moveDown();
                    break;
                case 32:
                    pause();
                    break;
                case 13:
                    moveBottom();
                    break;
                default:
                    break;
            }
            cout << endl;
        }
    }
}

bool crash(block BLOCK) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (BLOCK.x == 22 && BLOCK.y == 1) {
                return false;
            }
            if (windowShape[i + BLOCK.y + 1][j + BLOCK.x - 15] == 1 &&
                blockShape[BLOCK.blockIndex][BLOCK.blockStatus][i][j] == 1) {
                return true;
            }
        }
    }
    return false;
}

void copyBlock(block *current, block *next) {
    *current = *next;
    (*current).x = 22;
    (*current).y = 1;
}

void moveLeft() {
    deleteBlock(CURRENT);
    CURRENT.x -= 1;
    if (crash(CURRENT)) {
        CURRENT.x += 1;
    }
    displayBlock(CURRENT);
}

void moveRight() {
    deleteBlock(CURRENT);
    CURRENT.x += 1;
    if (crash(CURRENT)) {
        CURRENT.x -= 1;
    }
    displayBlock(CURRENT);
}

void rotate() {
    deleteBlock(CURRENT);
    CURRENT.blockStatus += 1;
    CURRENT.blockStatus %= 4;
    if (crash(CURRENT)) {
        if (CURRENT.blockStatus == 0) {
            CURRENT.blockStatus = 3;
        } else {
            CURRENT.blockStatus -= 1;
        }
    }
    displayBlock(CURRENT);
}

void moveDown() {
    //TODO
}

void pause() {
    for (;;) {
        if (getch() == 32) {
            break;
        }
    }
}

void moveBottom() {
    //TODO
}

void saveBlock() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blockShape[CURRENT.blockIndex][CURRENT.blockStatus][i][j] == 1) {
                windowShape[i + CURRENT.y][j + CURRENT.x - 15] = 1;
            }
        }
    }
}

void gameClose() {
    closeHandle();
    if (score > highest) {
        highest = score;
    }
    std::ofstream fout;
    fout.open("highest.bin", std::ios_base::binary | std::ios_base::trunc);
    fout << highest << endl;
    fout.close();
}