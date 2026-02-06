#include <iostream>

using namespace std;

int main()
{

    // 1.空指针拥有给指针变量进行初始化
    int *p = NULL;

    // 2.空指针的内存是无法被访问的
    // 0~255之间的内存编号是系统占用的，因此不可以被用户访问
    *p = 100; //  <==-=  会报错

    return 0;
}