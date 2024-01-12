#include <conio.h>
#include <random>
#include "game.h"
#include "core.h"
#include "data.h"

//游戏窗口渲染
int level = 1;
int score = 0;
int blockIndex;
int blockStatus;


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
    setTitle("Tetris");
    renderWindow(15, 0);
    displayUI();
    displayLevel(0);
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
    setPosition(9, 3);
    cout << "分数：" << score << endl;
    setPosition(9, 4);
    cout << "等级：" << level << endl;
}

void generateBlock(int x, int y, int color) {
    std::default_random_engine seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<> index(0,6);
    std::uniform_int_distribution<> status(0,3);
    blockIndex=index(gen);
    blockStatus=status(gen);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blockShape[blockIndex][blockStatus][i][j] == 1) {
                setColor(color);
                setPosition(x + j, y + i);
                cout << "■";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

void deleteBlock(int x,int y){
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(blockShape[blockIndex][blockStatus][i][j]==1){
                setPosition(x+j,y+i);
                cout << "  ";
            }
        }
    }
}

void moveBlock(){
    for(;;){
        if(kbhit()){
            switch (getch()) {
                case 'W':
                case 'w':
                case 72:
                    cout << "TEST_UP";
                    break;
                case 'A':
                case 'a':
                case 75:
                    cout << "TEST_LEFT";
                    break;
                case 'D':
                case 'd':
                case 77:
                    cout << "TEST_RIGHT";
                    break;
                case 'S':
                case 's':
                case 80:
                    cout << "TEST_DOWN";
                    break;
                case 32:
                    cout << "TEST_SPACE";
                    break;
                case 13:
                    cout << "TEST_ENTER";
                    break;
                default:
                    break;
            }
            cout << endl;
        }
    }
}

void moveLeft() {
    //TODO
}

void moveRight() {
    //TODO
}

void rotate() {
    //TODO
}

void moveDown() {
    //TODO
}

void pause() {
    //TODO
}

void moveBottom() {
    //TODO
}
