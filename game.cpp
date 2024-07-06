#include <conio.h>
#include <fstream>
#include <random>
#include "game.hpp"
#include "core.hpp"
#include "data.hpp"

///@��Ϸ���Ĵ���

const int WINDOW_WIDTH = 27;
const int WINDOW_HEIGHT = 25;
const int BLOCK_SIZE = 4;
int GAME_SPEED;
int score = 0;
int highest = 0;
int level = 0;
enum Direction {
    UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, SPACE = 32, ENTER = 13
};

Block CURRENT, NEXT;
bool musicStatus;

void soundControl(bool status) {
    if (status) {
        mciSendString("open .\\resources\\bg1.mp3 alias music", 0, 0, 0);
        mciSendString("play music repeat", 0, 0, 0);
    } else {
        mciSendString("stop music", 0, 0, 0);
        mciSendString("close music", 0, 0, 0);
    }
}

void setMusic() {
    system("cls");
    setColor(0x07);
    setCursorVisibility(0);
    setPosition(15, 0);
    cout << "�Ƿ����������֣�[Y/n]";
    setCursorVisibility(1);
    char musicFlag;
    cin.get(musicFlag);
    switch (musicFlag) {
        case 'N':
        case 'n':
            musicStatus = false;
            break;
        case 'Y':
        case 'y':
        default:
            musicStatus = true;
            break;
    }
    soundControl(musicStatus);
    setCursorVisibility(0);
}

void setDifficulty() {
    setColor(0x07);
    setPosition(15, 0);
    cout << "��ѡ����Ϸ�Ѷȡ�\n";
    setPosition(15, 1);
    cout << "1.��\n";
    setPosition(15, 2);
    cout << "2.�е�\n";
    setPosition(15, 3);
    cout << "3.����\n";
    setPosition(15, 4);
    setCursorVisibility(1);
    int difficulty;
    cin >> difficulty;
    cin.get();
    switch (difficulty) {
        case 1:
            GAME_SPEED = 0.6 * CLOCKS_PER_SEC;
            break;
        case 2:
            GAME_SPEED = 0.4 * CLOCKS_PER_SEC;
            break;
        case 3:
            GAME_SPEED = 0.2 * CLOCKS_PER_SEC;
            break;
        default:
            GAME_SPEED = 0.6 * CLOCKS_PER_SEC;
            break;
    }
    level = difficulty;
    setCursorVisibility(0);
    update();
}

void renderWindow(int x, int y) {
    system("cls");
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
    bool gameRun = 1;
    initHandle();
    setCursorVisibility(0);
    setTitle("Tetris");
    start();
    setDifficulty();
    setMusic();

    renderWindow(15, 0);
    readHighest();

    displayUI();
    displayScore(0);
    NEXT = Block();
    CURRENT = NEXT;
    NEXT = Block();
    NEXT.displaySelf();
    CURRENT.refresh();

    clock_t startTime = clock();
    clock_t stopTime;

    while (gameRun) {
        // ����Ƿ��а�������
        if (_kbhit()) {
            // �жϰ���
            switch (_getch()) {
                case 'w':
                case 'W':
                case UP:
                    CURRENT.rotate();
                    break;
                case 'a':
                case 'A':
                case LEFT:
                    CURRENT.moveLeft();
                    break;
                case 'd':
                case 'D':
                case RIGHT:
                    CURRENT.moveRight();
                    break;
                case 's':
                case 'S':
                case DOWN:
                    CURRENT.moveDown();
                    break;
                case SPACE:
                    pause();
                    break;
                case ENTER:
                    CURRENT.moveBottom();
                    break;
                case 'o':
                case 'O':
                    musicStatus = !musicStatus;
                    soundControl(musicStatus);
                    break;
            }
        }
        stopTime = clock();
        if (stopTime - startTime > GAME_SPEED) {
            if (CURRENT.moveDown() == -2) {
                gameRun = !gameRun;
            }
            startTime = stopTime;
            clearArea();
            NEXT.displaySelf();
        }
    }
    over();
    finish();
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
    setPosition(32, 17);
    cout << "�� O ��/�ر�����\n";
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
    cout << "������" << score << endl;
    setPosition(6, 4);
    cout << "��ʷ��ߣ�" << highest << endl;
    setPosition(6, 5);
    cout << "�Ѷȵȼ���" << level << endl;
}

void pause() {
    for (;;) {
        if (_getch() == 32) {
            break;
        }
    }
}

void update() {
    for (int i = 1; i < 24; i++) {
        for (int j = 1; j < 15; j++) {
            if (windowShape[i][j] == 1) {
                setColor(0x0e);
                setPosition(j + 15, i);
                cout << "��";
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
    soundControl(false);
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
            cout << "��";
            Sleep(5);
        }
    }
    setColor(0);
}

void finish() {
    setColor(0x0d);
    setPosition(21, 8);
    cout << "��Ϸ����";
    setPosition(16, 9);
    cout << "��Y���¿�ʼ";
    setPosition(23, 9);
    cout << "��N�˳���Ϸ";
    switch (_getch()) {
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
    printf("����������  ����������  ����������  ��������  ������    ��������");
    setPosition(x, y + 1);
    printf("    ��      ��              ��      ��    ��    ��    ��");
    setPosition(x, y + 2);
    printf("    ��      ��������        ��      ��������    ��      ������");
    setPosition(x, y + 3);
    printf("    ��      ��              ��      ��  ��      ��            ��");
    setPosition(x, y + 4);
    printf("    ��      ����������      ��      ��    ��  ������   ��������");
    setPosition(20, 15);
    printf("���س�����ʼ��Ϸ");
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
    int a = 5;
    printStart(a, 5);
    for (;;) {
        time2 = clock();
        if (time2 - time1 > 300) {
            time1 = time2;
            clearStart(a, 5);
            printStart(++a, 5);
            if (a == WINDOW_HEIGHT) {
                clearStart(a, 5);
                a = 0;
            }
        }
        if (_kbhit()) {
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
    cout << "��һ�����飺";
    setColor(0);
}

Block::Block() {
    std::random_device seed;
    std::mt19937 gen(seed());
    std::uniform_int_distribution<> index(0, 6);
    std::uniform_int_distribution<> status(0, 3);
    std::uniform_int_distribution<> colorGen(0x01, 0x0f);
    x = 32;
    y = 3;
    blockIndex = index(gen);
    blockStatus = status(gen);
    this->color = colorGen(gen);
}


void Block::displaySelf() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blockShape[blockIndex][blockStatus][i][j] == 1) {
                setColor(color);
                setPosition(x + j, y + i);
                cout << "��";
            }
        }
        setColor(0);
        cout << endl;
    }
}

void Block::deleteSelf() {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            if (blockShape[blockIndex][blockStatus][i][j] == 1) {
                setPosition(x + j, y + i);
                cout << "  ";
            }
        }
    }
}

int Block::Crash() {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            if (blockShape[blockIndex][blockStatus][i][j] == 1) {
                if (windowShape[i + y][j + x - 15] == 1) {
                    if (x == 22 && y == 2) {
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

void Block::moveLeft() {
    deleteSelf();
    x -= 1;
    if (Crash() == -1) {
        x += 1;
    }
    displaySelf();
}

void Block::moveRight() {
    deleteSelf();
    x += 1;
    if (Crash() == -1) {
        x -= 1;
    }
    displaySelf();
}

void Block::rotate() {
    deleteSelf();
    blockStatus += 1;
    blockStatus %= BLOCK_SIZE;
    if (Crash() == -1) {
        if (blockStatus == 0) {
            blockStatus = 3;
        } else {
            blockStatus -= 1;
        }
    }
    displaySelf();
}

inline int Block::moveDown() {
    deleteSelf();
    y += 1;
    if (Crash() == -1) {
        y -= 1;
        saveBlock();
        fullDetect();
        CURRENT = NEXT;
        NEXT = Block();
        CURRENT.refresh();
        update();
        return -1;
    } else if (Crash() == -2) {
        return -2;
    }
    displaySelf();
    return 0;
}

void Block::moveBottom() {
    for (;;) {
        deleteSelf();
        y += 1;
        if (Crash() == -1) {
            y -= 1;
            saveBlock();
            fullDetect();
            CURRENT = NEXT;
            NEXT = Block();
            CURRENT.refresh();
            update();
            return;
        } else if (Crash() == -2) {
            over();
            return;
        }
    }
}

void Block::saveBlock() {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            if (blockShape[blockIndex][blockStatus][i][j] == 1) {
                windowShape[i + y][j + x - 15] = 1;
            }
        }
    }
}

void Block::refresh() {
    x = 22;
    y = 1;
}
