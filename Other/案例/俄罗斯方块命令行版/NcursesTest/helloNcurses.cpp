#include <ncurses.h>

int main()
{
    initscr();                 // 1. 初始化屏幕，进入 curses 模式
    printw("Hello, Ncurses!"); // 2. 在逻辑屏幕 stdscr 的当前位置打印字符串
    refresh();                 // 3. 刷新屏幕，将逻辑屏幕的内容显示到物理屏幕上
    getch();                   // 4. 等待用户按键
    endwin();                  // 5. 结束 curses 模式，恢复终端到之前的状态

    return 0;
}