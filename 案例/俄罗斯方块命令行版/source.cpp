#include <iostream>
#include <string>

using namespace std;

wstring tetromino[7]; // 7种经典俄罗斯方块形状

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

int main()
{
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

    return 0;
}