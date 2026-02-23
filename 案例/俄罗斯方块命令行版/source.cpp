#include <iostream>
#include <string>
#include <ncurses.h>
#include <locale.h>

using namespace std;

wstring tetromino[7]; // 7种经典俄罗斯方块形状
int nFileWidth = 12;
int nFileHeight = 18;
unsigned char *pField = nullptr;

/**
 * 计算4x4网格中点(px, py)旋转r次后的位置索引
 * @param px: 点的x坐标 (0-3, 从左到右)
 * @param py: 点的y坐标 (0-3, 从上到下)
 * @param r: 旋转次数 (0=0°, 1=90°, 2=180°, 3=270°)
 * @return: 旋转后在4x4网格中的线性索引 (0-15)
 */
int Rotate(int px, int py, int r)
{
    switch (r % 4) // 取模确保旋转次数在0-3范围内
    {
    case 0:
        // 0度旋转：不旋转
        return py * 4 + px; // 旋转0度

    case 1:
        // 90度顺时针旋转
        return 12 + py - (px * 4); // 旋转90度

    case 2:
        // 180度旋转
        return 15 - (py * 4) - px; // 旋转180度

    case 3:
        // 270度顺时针旋转（或90度逆时针）
        return 3 - py + (px * 4); // 旋转270度
    }
    return 0; // 默认返回0（实际不会执行到这里）
}

void intNcurses()
{
    // 初始化ncurses环境（相当于创建屏幕缓冲区）
    setlocale(LC_ALL, ""); // 支持宽字符（对应你的wchar_t）
    initscr();             // 初始化屏幕（相当于CreateConsoleScreenBuffer）
    cbreak();              // 禁用行缓冲，立即响应按键
    noecho();              // 不显示输入的字符
    keypad(stdscr, TRUE);  // 启用功能键（方向键等）
    curs_set(0);           // 隐藏光标

    // ncurses会自动创建一个默认窗口stdscr
    // 不需要手动分配字符数组，ncurses内部已经管理了缓冲区

    // 获取屏幕尺寸
    int nScreenWidth, nScreenHeight;
    getmaxyx(stdscr, nScreenHeight, nScreenWidth); // 注意：顺序是(y,x)

    // 清屏（相当于你给每个字符赋值为空格）
    clear();

    // 刷新屏幕（相当于SetConsoleActiveScreenBuffer的效果）
    refresh();
}

void drawField()
{
    for (int y = 0; y < nFileHeight; y++)
    {
        for (int x = 0; x < nFileWidth; x++)
        {
            int idx = y * nFileWidth + x;
            // 使用颜色区分不同状态
            if (pField[idx] == 0)
            {
                attron(COLOR_PAIR(1)); // 黑色
                mvprintw(y, x, ".");
                attroff(COLOR_PAIR(1));
            }
            else if (pField[idx] == 9)
            {
                attron(COLOR_PAIR(2)); // 红色（边界）
                mvprintw(y, x, "#");
                attroff(COLOR_PAIR(2));
            }
            else
            {
                attron(COLOR_PAIR(3)); // 绿色（方块）
                mvprintw(y, x, "[]");
                attroff(COLOR_PAIR(3));
            }
        }
    }
}

int main()
{
    intNcurses();
    // === I 型 (长条) ===
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");

    // === O 型 (方形) ===
    tetromino[1].append(L"....");
    tetromino[1].append(L".XX.");
    tetromino[1].append(L".XX.");
    tetromino[1].append(L"....");

    // === T 型 ===
    tetromino[2].append(L"....");
    tetromino[2].append(L".XXX.");
    tetromino[2].append(L"..X..");
    tetromino[2].append(L"....");

    // === L 型 ===
    tetromino[3].append(L"....");
    tetromino[3].append(L"..X..");
    tetromino[3].append(L"..X..");
    tetromino[3].append(L"..XX.");

    // === J 型 (L的镜像) ===
    tetromino[4].append(L"....");
    tetromino[4].append(L"..X..");
    tetromino[4].append(L"..X..");
    tetromino[4].append(L".XX..");

    // === S 型 ===
    tetromino[5].append(L"....");
    tetromino[5].append(L"..XX.");
    tetromino[5].append(L".XX..");
    tetromino[5].append(L"....");

    // === Z 型 (S的镜像) ===
    tetromino[6].append(L"....");
    tetromino[6].append(L".XX..");
    tetromino[6].append(L"..XX.");
    tetromino[6].append(L"....");

    // 创建优势场地，“9”表示边界，“0”表示空白，
    // 这个双重循环遍历每一个格子，并给每个格子赋值
    pField = new unsigned char[nFileWidth * nFileHeight];
    for (int x = 0; x < nFileWidth; x++)
    {
        for (int y = 0; y < nFileHeight; y++)
        {
            pField[y * nFileWidth + x] = (x == 0 || x == nFileWidth - 1 || y == nFileHeight - 1) ? 9 : 0; // 先利用y坐标算出所对的行的开头的数值，再加上x坐标算出位置的数值，用一维数组表示二维数组，有利于减少CPU调用效率更高
        }
    }

    drawField();

    endwin();

    return 0;
}