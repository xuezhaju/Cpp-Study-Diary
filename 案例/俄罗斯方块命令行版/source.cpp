#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <locale.h>

using namespace std;
using namespace std::chrono_literals; // 使用 chrono 字面量，支持 50ms 这样的写法

// 存储7种经典俄罗斯方块的形状，每个都是4x4网格的字符串表示
wstring tetromino[7];

// 游戏场地的宽度和高度
int nFieldWidth = 12;
int nFieldHeight = 18;

// 游戏结束标志
bool bGameOver = false;

// 按键状态数组 [0]左, [1]右, [2]下, [3]旋转
bool bKey[4] = {false};
bool bLine;

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

// 显示字符映射表：索引0是空格(空白)，索引1-8对应字母，索引9是'#'(边界)
const wchar_t *cellChars = L" ABCDEFG=#";

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
    case 0:                        // 0度旋转：不旋转
        return py * 4 + px;        // 直接返回原始索引
    case 1:                        // 90度顺时针旋转
        return 12 + py - (px * 4); // 旋转90度后的索引计算公式
    case 2:                        // 180度旋转
        return 15 - (py * 4) - px; // 旋转180度后的索引计算公式
    case 3:                        // 270度顺时针旋转（或90度逆时针）
        return 3 - py + (px * 4);  // 旋转270度后的索引计算公式
    }
    return 0; // 默认返回0（实际不会执行到这里）
}

/**
 * 检查指定位置和旋转状态的方块是否与场地中的已有方块重叠（碰撞）
 * @param nTetromino: 方块类型索引 (0-6, 对应7种经典方块)
 * @param nRotation: 旋转状态 (0-3, 0=0°, 1=90°, 2=180°, 3=270°)
 * @param nPosX: 方块左上角在场地中的X坐标（列）
 * @param nPosY: 方块左上角在场地中的Y坐标（行）
 * @return: true = 可以放置（无碰撞），false = 不能放置（有碰撞）
 */
bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{
    // 遍历方块的4x4网格
    for (int px = 0; px < 4; px++) // px: 在方块自身4x4网格中的x坐标
    {
        for (int py = 0; py < 4; py++) // py: 在方块自身4x4网格中的y坐标
        {
            // 计算旋转后的方块格子在线性存储中的索引
            int pi = Rotate(px, py, nRotation);

            // 计算该格子在场地的实际位置索引（一维数组）
            int fi = (nPosY + py) * nFieldWidth + (nPosX + px);

            // 检查场地坐标是否在有效范围内（左右边界）
            if (nPosX + px >= 0 && nPosX + px < nFieldWidth)
            {
                // 检查场地坐标是否在有效范围内（上下边界）
                if (nPosY + py >= 0 && nPosY + py < nFieldHeight)
                {
                    // 核心碰撞检测：
                    // 如果方块的这个格子是实心的(L'X')，并且场地的这个位置已经被占用(pField[fi] != 0)
                    if (tetromino[nTetromino][pi] == L'X' && pField[fi] != 0)
                    {
                        return false; // 发生碰撞，不能放置
                    }
                }
            }
        }
    }
    return true; // 没有发现碰撞，可以放置
}

/**
 * 初始化 ncurses 库，设置终端显示模式
 */
void initNcurses()
{
    setlocale(LC_ALL, ""); // 设置本地化，支持宽字符显示
    initscr();             // 初始化屏幕，进入 curses 模式
    cbreak();              // 禁用行缓冲，字符输入后立即可用
    noecho();              // 不将输入的字符显示在屏幕上
    keypad(stdscr, TRUE);  // 启用功能键（方向键等）
    curs_set(0);           // 隐藏光标
    timeout(50);           // 设置getch()超时50ms，实现非阻塞输入
}

/**
 * 初始化7种俄罗斯方块的形状
 * 每个字符串16个字符，表示4x4网格，'X'表示实心，'.'表示空心
 */
void initTetromino()
{
    tetromino[0] = L"..X...X...X...X.";  // I型（长条）
    tetromino[1] = L".....XX..XX.....";  // O型（方形）
    tetromino[2] = L".....XXX..X......"; // T型
    tetromino[3] = L".....X...X...XX.."; // L型
    tetromino[4] = L".....X...X..XX..."; // J型（L的镜像）
    tetromino[5] = L".....XX..XX......"; // S型
    tetromino[6] = L".....XX..XX......"; // Z型（S的镜像）
}

/**
 * 整体初始化函数
 */
void init()
{
    initTetromino();                 // 初始化方块形状
    initNcurses();                   // 初始化 ncurses
    srand((unsigned int)time(NULL)); // 设置随机数种子，用于随机生成方块
}

/**
 * 创建游戏场地，初始化边界和空白区域
 * 9表示边界，0表示空白
 */
void createField()
{
    pField = new unsigned char[nFieldWidth * nFieldHeight]; // 动态分配场地内存
    for (int x = 0; x < nFieldWidth; x++)                   // 遍历每一列
    {
        for (int y = 0; y < nFieldHeight; y++) // 遍历每一行
        {
            // 边界条件：左边框(x=0)、右边框(x=nFieldWidth-1)、底部边框(y=nFieldHeight-1)
            pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;
        }
    }
}

/**
 * 处理游戏计时，控制下落速度
 */
void GameTiming()
{
    this_thread::sleep_for(50ms);           // 暂停50ms，控制游戏帧率
    nSpeedCounter++;                        // 增加计数器
    bForceDown = (nSpeed == nSpeedCounter); // 当计数器达到速度阈值时，强制下落
}

/**
 * 处理用户输入
 */
void InputEven()
{
    // 重置所有按键状态
    bKey[0] = false; // 左
    bKey[1] = false; // 右
    bKey[2] = false; // 下
    bKey[3] = false; // 旋转

    int key = getch(); // 获取按键输入（非阻塞，因为有timeout设置）

    // 根据不同的按键设置对应的状态
    if (key == KEY_LEFT) // 左箭头
    {
        bKey[0] = true;
    }
    else if (key == KEY_RIGHT) // 右箭头
    {
        bKey[1] = true;
    }
    else if (key == KEY_DOWN) // 下箭头
    {
        bKey[2] = true;
    }
    else if (key == ' ' || key == 'r' || key == 'R' || key == KEY_UP) // 空格、r键或上箭头用于旋转
    {
        bKey[3] = true;
    }
    else if (key == 'q' || key == 'Q') // q键退出游戏
    {
        bGameOver = true;
    }
}

/**
 * 更新游戏逻辑，处理方块移动、旋转和下落
 */
/**
 * 更新游戏逻辑，处理方块移动、旋转和下落
 */
void UpdateGame()
{
    // 左移：如果左键按下且左移后不会碰撞
    if (bKey[0] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY))
    {
        nCurrentX--; // 向左移动一格
    }

    // 右移：如果右键按下且右移后不会碰撞
    if (bKey[1] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY))
    {
        nCurrentX++; // 向右移动一格
    }

    // 加速下落：如果下键按下且下移后不会碰撞
    if (bKey[2] && DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
    {
        nCurrentY++; // 向下移动一格
    }

    // 旋转：如果旋转键按下且旋转后不会碰撞
    if (bKey[3] && DoesPieceFit(nCurrentPiece, (nCurrentRotation + 1) % 4, nCurrentX, nCurrentY))
    {
        nCurrentRotation = (nCurrentRotation + 1) % 4; // 旋转90度
    }

    // 强制下落（时间触发的自动下落）
    if (bForceDown)
    {
        // 如果能向下移动
        if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
        {
            nCurrentY++; // 向下移动一格
        }
        else // 不能向下移动了，方块应该固定
        {
            // ★ 修复1：只遍历方块的4x4网格，不是整个场地
            for (int px = 0; px < 4; px++)
            {
                for (int py = 0; py < 4; py++)
                {
                    // 计算旋转后的索引
                    int pi = Rotate(px, py, nCurrentRotation);

                    // 如果是实心格子
                    if (tetromino[nCurrentPiece][pi] == L'X')
                    {
                        // 计算在场地中的位置
                        int fieldX = nCurrentX + px;
                        int fieldY = nCurrentY + py;

                        // 确保在场地范围内
                        if (fieldX >= 0 && fieldX < nFieldWidth &&
                            fieldY >= 0 && fieldY < nFieldHeight)
                        {
                            // 将场地对应位置的值设置为方块类型+1
                            pField[fieldY * nFieldWidth + fieldX] = nCurrentPiece + 1;
                        }
                    }
                }
            }

            for (int py = 0; py < 4; py++)
            {
                if (nCurrentY + py < nFieldHeight - 1)
                {
                    bLine = true;
                    for (int px = 1; px < nFieldWidth - 1; px++)
                    {
                        bLine &= (pField[(nCurrentY + py) * nFieldWidth + px]) != 0;
                    }

                    if (bLine)
                    {
                        for (int px = 1; px < nFieldWidth--; px++)
                        {
                            pField[(nCurrentY + py) * nFieldWidth + px] = 8;
                        }
                    }
                }
            }

            // ★ 修复2：新方块的X坐标应该基于宽度，不是高度
            nCurrentX = nFieldWidth / 2 - 2; // 修正：使用宽度计算
            nCurrentY = 0;                   // 设置新方块的Y坐标（顶部）
            nCurrentRotation = 0;            // 重置旋转状态
            nCurrentPiece = rand() % 7;      // 随机选择下一个方块类型

            // 检查新方块是否能放置，如果不能，游戏结束
            bGameOver = !DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);

            // 可选：如果游戏结束，显示原因
            if (bGameOver)
            {
                mvprintw(3, 0, "游戏结束！新方块无法放置！");
            }
        }

        nSpeedCounter = 0; // 重置下落计数器
    }
}

/**
 * 绘制游戏画面
 */
void Draw()
{
    clear(); // 清空屏幕

    // 绘制场地（已经固定的方块和边界）
    for (int x = 0; x < nFieldWidth; x++)
    {
        for (int y = 0; y < nFieldHeight; y++)
        {
            int cellValue = pField[y * nFieldWidth + x]; // 获取该位置的数值
            wchar_t ch = cellChars[cellValue];           // 根据数值获取要显示的字符
            mvaddch(y + 2, x + 2, ch);                   // 在屏幕上的对应位置绘制（+2是边距）
        }
    }

    // 绘制当前正在下落的方块
    for (int px = 0; px < 4; px++) // 遍历方块的4列
    {
        for (int py = 0; py < 4; py++) // 遍历方块的4行
        {
            int pi = Rotate(px, py, nCurrentRotation); // 计算旋转后的索引
            if (tetromino[nCurrentPiece][pi] == L'X')  // 如果是实心格子
            {
                // 计算这个格子在场地中的实际位置
                int fieldX = nCurrentX + px;
                int fieldY = nCurrentY + py;

                // 确保在场地范围内
                if (fieldX >= 0 && fieldX < nFieldWidth && fieldY >= 0 && fieldY < nFieldHeight)
                {
                    // 绘制方块，用 'A' + nCurrentPiece 显示不同的字母
                    mvaddch(fieldY + 2, fieldX + 2, 'A' + nCurrentPiece);
                }
            }
        }
    }

    // 显示提示信息
    mvprintw(0, 0, "俄罗斯方块 - 按 'q' 退出");
    mvprintw(1, 0, "位置: (%d,%d) 旋转: %d", nCurrentX, nCurrentY, nCurrentRotation);

    refresh(); // 刷新屏幕，将缓冲区的内容显示出来
}

/**
 * 主函数
 */
int main()
{
    // 初始化游戏
    init();
    createField();

    // 游戏主循环
    while (!bGameOver) // 当游戏没有结束时循环
    {
        GameTiming();

        InputEven();  // 处理输入
        UpdateGame(); // 更新游戏逻辑
        Draw();       // 绘制画面
    }

    // 清理资源
    endwin();        // 结束 ncurses 模式，恢复终端设置
    delete[] pField; // 释放场地内存

    return 0; // 程序结束
}