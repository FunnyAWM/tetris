#include <conio.h>
#include <fstream>
#include <random>
#include <thread>
#include "game.h"
#include "core.h"
#include "data.h"

/**@游戏核心代码*/

const int WINDOW_WIDTH = 26;
const int WINDOW_HEIGHT = 25;
const int BLOCK_SIZE = 4;
const int GAME_SPEED = 0.45 * CLOCKS_PER_SEC;
int score = 0;
int highest = 0;
enum Direction {
    UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, SPACE = 32, ENTER = 13
};

extern block CURRENT, NEXT;

void renderWindow(int x, int y) {
    for (int i = 0; i < WINDOW_HEIGHT; i++) {
        for (int j = 0; j < WINDOW_WIDTH; j++) {
            if (windowShape[i][j] == 1) {
                setColor(0xc0);
                setPosition(j + x, i + y);
                cout << "  ";
            }
        }
    }
}

void gameInit() {
    int gameRun = 1;
    initHandle();
    setCursorVisibility(0);
    start();
    setTitle("Tetris");

    renderWindow(15, 0);
    readHighest();

    displayUI();
    displayScore(0);
    generateBlock();
    copyBlock(&CURRENT, &NEXT);
    generateBlock();
    displayBlock(NEXT);

    clock_t startTime = clock();
    clock_t stopTime;

    while (gameRun) {
        // 检测是否有按键按下
        if (kbhit()) {
            // 判断按键
            switch (getch()) {
                case 'w':
                case 'W':
                case UP:
                    rotate();
                    break;
                case 'a':
                case 'A':
                case LEFT:
                    moveLeft();
                    break;
                case 'd':
                case 'D':
                case RIGHT:
                    moveRight();
                    break;
                case 's':
                case 'S':
                case DOWN:
                    moveDown();
                    break;
                case SPACE:
                    pause();
                    break;
                case ENTER:
                    moveBottom();
                    break;

            }
        }
        stopTime = clock();
        if (stopTime - startTime > GAME_SPEED) {
            if (moveDown() == -2) {
                gameRun = 0;
            }
            startTime = stopTime;
            clearArea();
            displayBlock(NEXT);
        }
    }
    over();
    finish();
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

void displayScore(int num) {
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
    cout << "历史最高：" << highest << endl;
}

void generateBlock() {
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<> index(0, 6);
    std::uniform_int_distribution<> status(0, 3);
    std::uniform_int_distribution<> color(0x01, 0x0f);
    NEXT.x = 32;
    NEXT.y = 3;
    NEXT.blockIndex = index(gen);
    NEXT.blockStatus = status(gen);
    NEXT.color = color(gen);
}


inline void displayBlock(const block BLOCK) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blockShape[BLOCK.blockIndex][BLOCK.blockStatus][i][j] == 1) {
                setColor(BLOCK.color);
                setPosition(BLOCK.x + j, BLOCK.y + i);
                cout << "■";
            }
        }
        setColor(0);
        cout << endl;
    }
}


inline void deleteBlock(block BLOCK) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            if (blockShape[BLOCK.blockIndex][BLOCK.blockStatus][i][j] == 1) {
                setPosition(BLOCK.x + j, BLOCK.y + i);
                cout << "  ";
            }
        }
    }
}

int crash(block BLOCK) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            if (blockShape[BLOCK.blockIndex][BLOCK.blockStatus][i][j] == 1) {
                if (windowShape[i + BLOCK.y][j + BLOCK.x - 15] == 1) {
                    if (BLOCK.x == 22 && BLOCK.y == 2) {
                        return -2;
                    } else {
                        return -1;
                    }
                }
            }
        }
    }
    return 0;
}

void copyBlock(block *current, block *next) {
    *current = *next;
    (*current).x = 22;
    (*current).y = 1;
    generateBlock();
}

void moveLeft() {
    deleteBlock(CURRENT);
    CURRENT.x -= 1;
    if (crash(CURRENT) == -1) {
        CURRENT.x += 1;
    }
    displayBlock(CURRENT);
}

void moveRight() {
    deleteBlock(CURRENT);
    CURRENT.x += 1;
    if (crash(CURRENT) == -1) {
        CURRENT.x -= 1;
    }
    displayBlock(CURRENT);
}

void rotate() {
    deleteBlock(CURRENT);
    CURRENT.blockStatus += 1;
    CURRENT.blockStatus %= BLOCK_SIZE;
    if (crash(CURRENT) == -1) {
        if (CURRENT.blockStatus == 0) {
            CURRENT.blockStatus = 3;
        } else {
            CURRENT.blockStatus -= 1;
        }
    }
    displayBlock(CURRENT);
}

inline int moveDown() {
    deleteBlock(CURRENT);
    CURRENT.y += 1;
    if (crash(CURRENT) == -1) {
        CURRENT.y -= 1;
        saveBlock();
        fullDetect();
        copyBlock(&CURRENT, &NEXT);
        update();
        return -1;
    } else if (crash(CURRENT) == -2) {
        return -2;
    }
    displayBlock(CURRENT);
    return 0;
}

void pause() {
    for (;;) {
        if (getch() == 32) {
            break;
        }
    }
}

void moveBottom() {
    for (;;) {
        deleteBlock(CURRENT);
        CURRENT.y += 1;
        if (crash(CURRENT) == -1) {
            CURRENT.y -= 1;
            saveBlock();
            fullDetect();
            copyBlock(&CURRENT, &NEXT);
            generateBlock();
            update();
            return;
        } else if (crash(CURRENT) == -2) {
            over();
            return;
        }
    }
}

void saveBlock() {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            if (blockShape[CURRENT.blockIndex][CURRENT.blockStatus][i][j] == 1) {
                windowShape[i + CURRENT.y][j + CURRENT.x - 15] = 1;
            }
        }
    }
}

void update() {
    for (int i = 1; i < 24; i++) {
        for (int j = 1; j < 15; j++) {
            if (windowShape[i][j] == 1) {
                setColor(0x0e);
                setPosition(j + 15, i);
                cout << "■";
            } else {
                setColor(0);
                setPosition(j + 15, i);
                cout << "  ";
            }
        }
    }
}

void fullDetect() {
    int num = 0;
    for (int i = 23; i > 1; i--) {
        int total = 0;
        for (int j = 1; j < 15; j++) {
            if (windowShape[i][j] == 1) {
                total++;
            }
        }
        if (total == 14) {
            fullDown(i);
            i += 1;
            num += 1;
        }
    }
    displayScore(num);
}

void fullDown(int lines) {
    for (int i = lines; i > 1; i--) {
        for (int j = 1; j < 15; j++) {
            windowShape[i][j] = windowShape[i - 1][j];
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

void over() {
    setColor(0x76);
    for (int i = 23; i > 0; i--) {
        for (int j = 14; j > 0; j--) {
            setPosition(j + 15, i);
            cout << "★";
            Sleep(5);
        }
    }
    setColor(0);
}

void finish() {
    setColor(0x0d);
    setPosition(21, 8);
    cout << "游戏结束";
    setPosition(16, 9);
    cout << "按Y重新开始";
    setPosition(23, 9);
    cout << "按N退出游戏";
    switch (getch()) {
        case 'Y':
        case 'y':
            again();
            break;
        case 'N':
        case 'n':
            gameClose();
            break;
        default:
            finish();
            break;
    }
}

void again() {
    setColor(0);
    system("cls");
    for (int i = 1; i < 24; i++) {
        for (int j = 1; j < 15; j++) {
            windowShape[i][j] = 0;
        }
    }
    gameInit();
}

void printStart(int x, int y) {
    int color = rand() % 0x10;
    if (color == 0x00) {
        color = 0x0f;
    }
    setColor(color);
    setPosition(x, y);
    printf("■■■■■  ■■■■■  ■■■■■  ■■■■  ■■■    ■■■■");
    setPosition(x, y + 1);
    printf("    ■      ■              ■      ■    ■    ■    ■");
    setPosition(x, y + 2);
    printf("    ■      ■■■■        ■      ■■■■    ■      ■■■");
    setPosition(x, y + 3);
    printf("    ■      ■              ■      ■  ■      ■            ■");
    setPosition(x, y + 4);
    printf("    ■      ■■■■■      ■      ■    ■  ■■■   ■■■■");
    setPosition(20, 15);
    printf("按回车键开始游戏");
}

void clearStart(int x, int y) {
    for (int i = y; i <= y + 4; i++) {
        for (int j = x; j <= x + 33; j++) {
            setPosition(j, i);
            cout << "  ";
        }
    }
}

void start() {
    clock_t time1, time2;
    time1 = clock();
    int x = 5;
    printStart(x, 5);
    for (;;) {
        time2 = clock();
        if (time2 - time1 > 300) {
            time1 = time2;
            clearStart(x, 5);
            printStart(++x, 5);
            if (x == WINDOW_HEIGHT) {
                clearStart(x, 5);
                x = 0;
            }
        }
        if (kbhit()) {
            cin.get();
            break;
        }
    }
    system("cls");
}

void readHighest() {
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
}

inline void clearArea() {
    for (int i = 31; i < 39; i++) {
        for (int j = 1; j < 7; j++) {
            setPosition(i, j);
            cout << "  ";
        }
    }
    setColor(0x0a);
    setPosition(31, 1);
    cout << "下一个方块：";
    setColor(0);
}