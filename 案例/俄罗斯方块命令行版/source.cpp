#include <iostream>
#include <string>
#include <ncurses.h>
#include <locale.h>

using namespace std;

wstring tetromino[7]; // 7种经典俄罗斯方块形状
int nFieldWidth = 12;
int nFieldHeight = 18;
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

// 判断方块是否符合旋转移动的条件
/**
 * 检查指定位置和旋转状态的方块是否与场地中的已有方块重叠（碰撞）
 *
 * @param nTetromino: 方块类型索引 (0-6, 对应7种经典方块)
 * @param nRotation: 旋转状态 (0-3, 0=0°, 1=90°, 2=180°, 3=270°)
 * @param nPosX: 方块自身4x4网格中左上角在场地中的X坐标（列）
 * @param nPosY: 方块自身4x4网格中左上角在场地中的Y坐标（行）
 * @return: true = 可以放置（无碰撞），false = 不能放置（有碰撞）
 */
bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{
    // 遍历方块的4x4网格
    // px: 在方块自身4x4网格中的x坐标 (0-3, 从左到右)
    // py: 在方块自身4x4网格中的y坐标 (0-3, 从上到下)
    for (int px = 0; px < 4; px++)
    {
        for (int py = 0; py < 4; py++)
        {
            // 步骤1: 计算旋转后的方块格子索引
            // pi = 旋转后该格子在tetromino字符串中的位置
            // Rotate函数根据(px,py)和旋转次数nRotation，返回旋转后的索引
            int pi = Rotate(px, py, nRotation);

            // 步骤2: 计算该格子在场地的实际位置索引
            // (nPosY + py): 方块py行 + 方块左上角Y坐标 = 场地的实际行
            // (nPosX + px): 方块px列 + 方块左上角X坐标 = 场地的实际列
            // 然后转换为一维数组索引: 行 * 总宽度 + 列
            int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

            // 步骤3: 检查场地坐标是否在有效范围内
            // 确保计算出的场地位置没有超出左右边界
            if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
            {
                // 确保计算出的场地位置没有超出上下边界
                if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
                {
                    // 步骤4: 核心碰撞检测！
                    // 条件1: tetromino[nTetromino][pi] == L'X'
                    //         -> 当前方块的这个格子是实心的（有方块）
                    // 条件2: pField[fi] != 0
                    //         -> 场地的这个位置已经被占用（不是空白）
                    //
                    // 如果两个条件都成立，说明方块的一个实心格子
                    // 碰到了场地上已有的方块或边界，发生碰撞
                    if (tetromino[nTetromino][pi] == L'X' && pField[fi] != 0)
                    {
                        return false; // 碰撞！不能放置
                    }
                }
            }
        }
    }

    // 所有格子检查完毕，没有发现碰撞
    return true; // 可以放置
}

void initNcurses()
{
    // 初始化ncurses环境（相当于创建屏幕缓冲区）
    setlocale(LC_ALL, ""); // 支持宽字符（对应你的wchar_t）
    initscr();             // 初始化屏幕（相当于CreateConsoleScreenBuffer）
    cbreak();              // 禁用行缓冲，立即响应按键
    noecho();              // 不显示输入的字符
    keypad(stdscr, TRUE);  // 启用功能键（方向键等）
    curs_set(0);           // 隐藏光标
    timeout(100);          // 设置getch()超时100ms，用于游戏循环
}

void initTetromino()
{
    // 初始化方块形状
    tetromino[0] = L"..X...X...X...X.";  // I
    tetromino[1] = L".....XX..XX.....";  // O
    tetromino[2] = L".....XXX..X......"; // T
    tetromino[3] = L".....X...X...XX.."; // L
    tetromino[4] = L".....X...X..XX..."; // J
    tetromino[5] = L".....XX..XX......"; // S
    tetromino[6] = L".....XX..XX......"; // Z
}

void GameTiming()
{
}

void GameLogic()
{
}

void gInputEven()
{
}

int main()
{
    initTetromino();

    // 创建优势场地，“9”表示边界，“0”表示空白，
    // 这个双重循环遍历每一个格子，并给每个格子赋值
    pField = new unsigned char[nFieldWidth * nFieldHeight];
    for (int x = 0; x < nFieldWidth; x++)
    {
        for (int y = 0; y < nFieldHeight; y++)
        {
            // 边界条件：左边框(x=0)、右边框(x=nFieldWidth-1)、底部边框(y=nFieldHeight-1)
            pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;
        }
    }

    // 初始化ncurses（只调用一次）
    initNcurses();

    bool bGameOver = false;

    // 修正：根据cellValue索引字符
    // 0: 空格 (空白区域)
    // 9: '#' (边界)
    const wchar_t *cellChars = L" ABCDEFG=#"; // 索引0-8是空格，索引9是#

    while (!bGameOver)
    {
        // 清屏
        clear();

        // 绘制场地
        for (int x = 0; x < nFieldWidth; x++)
        {
            for (int y = 0; y < nFieldHeight; y++)
            {
                int cellValue = pField[y * nFieldWidth + x];

                wchar_t ch = cellChars[cellValue]; // 现在用cellValue作为索引

                // 绘制到屏幕, + 是为了不紧贴边框
                mvaddch(y + 2, x + 2, ch);
            }
        }

        // 添加一些提示文字
        mvprintw(0, 0, "俄罗斯方块 - 按 'q' 退出");
        // mvprintw(nFieldHeight + 3, 0, "边界用 # 显示");

        // 刷新显示
        refresh();

        // 处理按键
        int key = getch();
        if (key == 'q' || key == 'Q')
        {
            break; // 退出游戏循环
        }
    }

    // 清理ncurses
    endwin();

    // 释放内存
    delete[] pField;

    return 0;
}