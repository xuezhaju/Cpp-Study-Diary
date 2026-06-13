#include <iostream>
using namespace std;


int& test01()
{
    int a = 10; //局部变量存放在四区中的 zhai区（怎么输入法打不出来这个字qwq）

    return a;
}

int& test02()
{
    static int b = 10;    // static修饰的是静态变量，处于全局区, 由程序结束之后系统自动释放

    return b;
}

int main()
{
    // 引用做函数的返回值
    // 1.不要返回局部变量的引用
    // int &ret = test01();
    int &ret = test02();

    cout << ret << endl;  // 如果是 int &ret = test01()的情况下，悬空引用

    test02() = 1000;  // 如果函数的返回值是一个引用，则函数调用可以作为一个左值

    cout << ret << endl;
    
    return 0;
}
