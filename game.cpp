#include <cmath>
#include <random>
#include "game.h"
#include "core.h"
#include "data.h"

//��Ϸ������Ⱦ
int level = 1;
int score = 0;

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
    cout << "����˵����";
    setColor(0x0b);
    setPosition(32, 11);
    cout << "�� A ����\n";
    setPosition(32, 12);
    cout << "�� D ����\n";
    setPosition(32, 13);
    cout << "�� W ��ת\n";
    setPosition(32, 14);
    cout << "�� S ��������\n";
    setPosition(32, 15);
    cout << "�� �ո� ��ͣ\n";
    setPosition(32, 16);
    cout << "�� �س� ֱ������\n";
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
    cout << "������" << score << endl;
    setPosition(9, 4);
    cout << "�ȼ���" << level << endl;
}

void displayBlock(int x, int y, int color) {
    std::default_random_engine seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<> index(0,6);
    std::uniform_int_distribution<> status(0,3);
    int blockIndex=index(gen);
    int blockStatus=status(gen);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blockShape[blockIndex][blockStatus][i][j] == 1) {
                setColor(color);
                setPosition(x + j, y + i);
                cout << "��";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }
}