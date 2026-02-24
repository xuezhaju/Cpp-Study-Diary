#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <ncurses.h>
#include <locale.h>

using namespace std;
using namespace std::chrono_literals;

// 存储7种经典俄罗斯方块的形状，每个都是4x4网格的字符串表示
wstring tetromino[7];

// 游戏场地的宽度和高度
int nFieldWidth = 12;
int nFieldHeight = 18;

// 游戏结束标志
bool bGameOver = false;

// 按键状态数组 [0]左, [1]右, [2]下, [3]旋转
bool bKey[4] = {false};

// 存储需要消除的行
vector<int> vLines;

// 游戏场地数据，一维数组表示二维场地，每个元素代表一个格子
unsigned char *pField = nullptr;

// 当前正在下落的方块信息
int nCurrentPiece = 2;               // 当前方块类型（0-6）
int nCurrentRotation = 0;            // 当前旋转状态（0-3）
int nCurrentX = nFieldWidth / 2 - 2; // 当前方块左上角的X坐标
int nCurrentY = 0;                   // 当前方块左上角的Y坐标

// 下落速度控制
int nSpeed = 20;         // 下落速度阈值（每20帧下落一次）
int nSpeedCounter = 0;   // 帧数计数器
bool bForceDown = false; // 强制下落标志

// 显示字符映射表：索引0是空格(空白)，索引1-7对应字母(A-G)，索引8是'='，索引9是'#'(边界)
const wchar_t *cellChars = L" ABCDEFG=#";

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

/**
 * 初始化 ncurses 库
 */
void initNcurses()
{
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(50);
}

/**
 * 初始化7种俄罗斯方块的形状
 */
void initTetromino()
{
    tetromino[0] = L"..X...X...X...X.";  // I型
    tetromino[1] = L".....XX..XX.....";  // O型
    tetromino[2] = L".....XXX..X......"; // T型
    tetromino[3] = L".....X...X...XX.."; // L型
    tetromino[4] = L".....X...X..XX..."; // J型
    tetromino[5] = L".....XX..XX......"; // S型
    tetromino[6] = L".....XX..XX......"; // Z型
}

/**
 * 整体初始化函数
 */
void init()
{
    initTetromino();
    initNcurses();
    srand((unsigned int)time(NULL));
}

/**
 * 创建游戏场地
 */
void createField()
{
    pField = new unsigned char[nFieldWidth * nFieldHeight];
    for (int x = 0; x < nFieldWidth; x++)
    {
        for (int y = 0; y < nFieldHeight; y++)
        {
            pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;
        }
    }
}

/**
 * 处理游戏计时
 */
void GameTiming()
{
    this_thread::sleep_for(20ms);
    nSpeedCounter++;
    bForceDown = (nSpeed == nSpeedCounter);
}

/**
 * 处理用户输入
 */
void InputEven()
{
    bKey[0] = false;
    bKey[1] = false;
    bKey[2] = false;
    bKey[3] = false;

    int key = getch();

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

/**
 * 消除满行
 */
void ClearLines()
{
    if (vLines.empty())
        return;

    // 从下往上消除行
    for (int line : vLines)
    {
        // 将该行上方的所有行向下移动
        for (int y = line; y > 0; y--)
        {
            for (int x = 1; x < nFieldWidth - 1; x++)
            {
                pField[y * nFieldWidth + x] = pField[(y - 1) * nFieldWidth + x];
            }
        }

        // 将最上面一行清空
        for (int x = 1; x < nFieldWidth - 1; x++)
        {
            pField[x] = 0; // 第0行清空
        }
    }

    vLines.clear(); // 清空行向量
}

/**
 * 更新游戏逻辑
 */
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

    // 加速下落
    if (bKey[2] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
    {
        nCurrentY++;
    }

    // 旋转
    if (bKey[3] && DoesPieceFit(nCurrentPiece, (nCurrentRotation + 1) % 4, nCurrentX, nCurrentY))
    {
        nCurrentRotation = (nCurrentRotation + 1) % 4;
    }

    // 强制下落
    if (bForceDown)
    {
        if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
        {
            nCurrentY++;
        }
        else // 方块固定
        {
            // 将当前方块锁定到场地
            for (int px = 0; px < 4; px++)
            {
                for (int py = 0; py < 4; py++)
                {
                    int pi = Rotate(px, py, nCurrentRotation);
                    if (tetromino[nCurrentPiece][pi] == L'X')
                    {
                        int fieldX = nCurrentX + px;
                        int fieldY = nCurrentY + py;

                        if (fieldX >= 1 && fieldX < nFieldWidth - 1 &&
                            fieldY >= 0 && fieldY < nFieldHeight - 1)
                        {
                            pField[fieldY * nFieldWidth + fieldX] = nCurrentPiece + 1;
                        }
                    }
                }
            }

            // 检查并收集需要消除的行
            vLines.clear();
            for (int py = nCurrentY; py < nCurrentY + 4; py++)
            {
                if (py < nFieldHeight - 1) // 不检查底部边界
                {
                    bool bLineFull = true;
                    for (int px = 1; px < nFieldWidth - 1; px++)
                    {
                        if (pField[py * nFieldWidth + px] == 0)
                        {
                            bLineFull = false;
                            break;
                        }
                    }
                    if (bLineFull)
                    {
                        vLines.push_back(py);
                    }
                }
            }

            // 生成下一个方块
            nCurrentX = nFieldWidth / 2 - 2;
            nCurrentY = 0;
            nCurrentRotation = 0;
            nCurrentPiece = rand() % 7;

            // 检查游戏是否结束
            bGameOver = !DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);
        }

        nSpeedCounter = 0;
    }
}

/**
 * 绘制游戏画面
 */
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

                if (fieldX >= 0 && fieldX < nFieldWidth &&
                    fieldY >= 0 && fieldY < nFieldHeight)
                {
                    mvaddch(fieldY + 2, fieldX + 2, 'A' + nCurrentPiece);
                }
            }
        }
    }

    // 如果有待消除的行，短暂显示特殊效果
    if (!vLines.empty())
    {
        // 用 '=' 标记要消除的行
        for (int line : vLines)
        {
            for (int x = 1; x < nFieldWidth - 1; x++)
            {
                mvaddch(line + 2, x + 2, '=');
            }
        }
        refresh();
        this_thread::sleep_for(200ms); // 短暂暂停，让玩家看到消除的行
        ClearLines();                  // 消除行
    }

    // 显示提示信息
    mvprintw(0, 0, "俄罗斯方块 - 按 'q' 退出");
    mvprintw(1, 0, "位置: (%d,%d) 旋转: %d  消除行数: %zu",
             nCurrentX, nCurrentY, nCurrentRotation, vLines.size());

    refresh();
}

/**
 * 主函数
 */
int main()
{
    init();
    createField();

    while (!bGameOver)
    {
        GameTiming();
        InputEven();
        UpdateGame();
        Draw();
    }

    // 显示游戏结束信息
    clear();
    mvprintw(10, 10, "游戏结束！按任意键退出...");
    refresh();
    getch();

    endwin();
    delete[] pField;

    return 0;
}