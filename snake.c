#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 20
#define MAX_LENGTH (WIDTH*HEIGHT)

// グローバル変数
int headX, headY;
int fruitX, fruitY;
int score;
int gameOver;
int tailX[MAX_LENGTH], tailY[MAX_LENGTH];
int tailLength;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
enum eDirection dir;

// 初期化関数
void Initialize()
{
    gameOver = 0;
    dir = STOP;
    headX = WIDTH / 2;
    headY = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
}

// フレーム描画関数
void DrawFrame()
{
    system("cls");
    int i, j;
    for (i = 0; i < WIDTH + 2; i++) {
        printf("■");
    }
    printf("\n");

    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if (j == 0) {
                printf("■");
            }

            if (i == headY && j == headX) {
                printf("●"); // ヘビの頭部
            }
            else if (i == fruitY && j == fruitX) {
                printf("◎"); // フルーツ
            }
            else {
                int isTail = 0;
                int k;
                for (k = 0; k < tailLength; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        printf("■"); // ヘビの体部
                        isTail = 1;
                    }
                }
                if (!isTail) {
                    printf("  "); // 空白
                }
            }

            if (j == WIDTH - 1) {
                printf("■");
            }
        }
        printf("\n");
    }

    for (i = 0; i < WIDTH + 2; i++) {
        printf("■");
    }
    printf("\n");
    printf("Score: %d\n", score);
}

// 入力受付関数
void Input()
{
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = 1;
            break;
        }
    }
}

// 更新関数
void Update()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = headX;
    tailY[0] = headY;
    int i;
    for (i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    }

    // ゲームオーバーの条件
    if (headX < 0 || headX >= WIDTH || headY < 0 || headY >= HEIGHT) {
        gameOver = 1;
    }

    for (i = 0; i < tailLength; i++) {
        if (tailX[i] == headX && tailY[i] == headY) {
            gameOver = 1;
            break;
        }
    }

    // フルーツを取った場合
    if (headX == fruitX && headY == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        tailLength++;
    }
}

int main()
{
    // ゲームの初期化
    Initialize();

    while (!gameOver) {
        // フレームの描画
        DrawFrame();

        // 入力の受付
        Input();

        // ゲームの更新
        Update();

        // 速度調整
        Sleep(10);
    }

    printf("ゲームオーバー\n");
    printf("最終スコア: %d\n", score);

    return 0;
}

