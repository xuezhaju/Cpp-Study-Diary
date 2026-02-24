#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <locale.h>

using namespace std;
using namespace std::chrono_literals;

wstring tetromino[7]; // 7种经典俄罗斯方块形状
int nFieldWidth = 12;
int nFieldHeight = 18;
bool bGameOver = false;
bool bKey[4] = {false}; // [0]左, [1]右, [2]下, [3]旋转
unsigned char *pField = nullptr;

int nCurrentPiece = 2;
int nCurrentRotation = 0;
int nCurrentX = nFieldWidth / 2 - 2;
int nCurrentY = 0;

int nSpeed = 20;
int nSpeedCounter = 0;
bool bForceDown = false;

const wchar_t *cellChars = L" ABCDEFG=#"; // 索引0是空格，索引9是#

/**
 * 计算4x4网格中点(px, py)旋转r次后的位置索引
 */
int Rotate(int px, int py, int r)
{
    switch (r % 4)
    {
    case 0:
        return py * 4 + px;
    case 1:
        return 12 + py - (px * 4);
    case 2:
        return 15 - (py * 4) - px;
    case 3:
        return 3 - py + (px * 4);
    }
    return 0;
}

/**
 * 检查指定位置和旋转状态的方块是否与场地中的已有方块重叠（碰撞）
 */
bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{
    for (int px = 0; px < 4; px++)
    {
        for (int py = 0; py < 4; py++)
        {
            int pi = Rotate(px, py, nRotation);
            int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

            if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
            {
                if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
                {
                    if (tetromino[nTetromino][pi] == L'X' && pField[fi] != 0)
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void initNcurses()
{
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(50); // 设置getch()超时50ms
}

void initTetromino()
{
    tetromino[0] = L"..X...X...X...X.";  // I
    tetromino[1] = L".....XX..XX.....";  // O
    tetromino[2] = L".....XXX..X......"; // T
    tetromino[3] = L".....X...X...XX.."; // L
    tetromino[4] = L".....X...X..XX..."; // J
    tetromino[5] = L".....XX..XX......"; // S
    tetromino[6] = L".....XX..XX......"; // Z
}

void createField()
{
    pField = new unsigned char[nFieldWidth * nFieldHeight];
    for (int x = 0; x < nFieldWidth; x++)
    {
        for (int y = 0; y < nFieldHeight; y++)
        {
            // 边界：左右边框和底部边框
            pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;
        }
    }
}

void InputEven()
{
    // 重置按键状态
    bKey[0] = false; // 左
    bKey[1] = false; // 右
    bKey[2] = false; // 下
    bKey[3] = false; // 旋转

    int key = getch();

    // 处理按键
    if (key == KEY_LEFT)
    {
        bKey[0] = true;
    }
    else if (key == KEY_RIGHT)
    {
        bKey[1] = true;
    }
    else if (key == KEY_DOWN)
    {
        bKey[2] = true;
    }
    else if (key == ' ' || key == 'r' || key == 'R' || key == KEY_UP)
    {
        bKey[3] = true;
    }
    else if (key == 'q' || key == 'Q')
    {
        bGameOver = true;
    }
}

void UpdateGame()
{
    // 左移
    if (bKey[0] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY))
    {
        nCurrentX--;
    }

    // 右移
    if (bKey[1] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY))
    {
        nCurrentX++;
    }

    // 下移（加速下落）
    if (bKey[2] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
    {
        nCurrentY++;
    }

    // 旋转
    if (bKey[3] && DoesPieceFit(nCurrentPiece, (nCurrentRotation + 1) % 4, nCurrentX, nCurrentY))
    {
        nCurrentRotation = (nCurrentRotation + 1) % 4;
    }

    // 自动下落（每8帧下落一次）
    static int fallCounter = 0;
    fallCounter++;
    if (fallCounter >= 8)
    {
        if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
        {
            nCurrentY++;
        }
        else
        {
            // 方块不能再下落了，固定到场地中
            // 这里先简单处理，后续添加固定方块的逻辑
        }
        fallCounter = 0;
    }
}

void Draw()
{
    clear();

    // 绘制场地
    for (int x = 0; x < nFieldWidth; x++)
    {
        for (int y = 0; y < nFieldHeight; y++)
        {
            int cellValue = pField[y * nFieldWidth + x];
            wchar_t ch = cellChars[cellValue];
            mvaddch(y + 2, x + 2, ch);
        }
    }

    // 绘制当前方块
    for (int px = 0; px < 4; px++)
    {
        for (int py = 0; py < 4; py++)
        {
            int pi = Rotate(px, py, nCurrentRotation);
            if (tetromino[nCurrentPiece][pi] == L'X')
            {
                int fieldX = nCurrentX + px;
                int fieldY = nCurrentY + py;

                if (fieldX >= 0 && fieldX < nFieldWidth && fieldY >= 0 && fieldY < nFieldHeight)
                {
                    mvaddch(fieldY + 2, fieldX + 2, 'A' + nCurrentPiece);
                }
            }
        }
    }

    // 显示提示信息
    mvprintw(0, 0, "俄罗斯方块 - 按 'q' 退出");
    mvprintw(1, 0, "位置: (%d,%d) 旋转: %d", nCurrentX, nCurrentY, nCurrentRotation);

    refresh();
}

int main()
{
    // 初始化
    initNcurses();
    initTetromino();
    createField();

    // 游戏主循环
    while (!bGameOver)
    {
        this_thread::sleep_for(50ms);

        // 输入处理
        InputEven();

        // 更新游戏逻辑
        UpdateGame();

        // 绘制
        Draw();

        // 控制帧率
        auto endTime = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        if (elapsed < 50ms)
        {
            this_thread::sleep_for(50ms - elapsed);
        }
    }

    // 清理
    endwin();
    delete[] pField;

    return 0;
}