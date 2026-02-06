#include <iostream>

using namespace std;

int main()
{
    /*
    常量指针  指向的内容是常量
    指针常量  指针本身是常量
    */

    // const修饰指针——常量指针
    // 可以改指针指向，不可以改值
    int a = 10;
    const int *p = &a;

    // const 修饰常量——指针常量
    int b = 20;
    int *const p = &b;

    /*
    常量指针：常量的指针；

    指针常量：指针是常量
    */

    // 常量指针常量
    // 指针的值和指向都不可以改

    return 0;
}