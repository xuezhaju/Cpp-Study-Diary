#include <iostream>

using namespace std;

// 引用传递

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}


int main()
{
    int a = 10;
    int b= 20;

    swap(a, b);

    cout << a << endl;
    cout << b << endl;

    return 0;
}

/*解释
 引用解释起别名，指向的都是一个内存，
 所以在swap函数中的 a 其实是在对main函数中的a进行操作
 因为起别名的变量修改了，原名变量也会修改
 是同步的
 所以这个方法会比用指针修改方便一些
 */
