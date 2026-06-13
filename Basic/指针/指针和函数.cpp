#include <iostream>

using namespace std;

void swap01(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;

    cout << "swap01:" << a << b << endl;
}

void swap02(int *p1, int *p2)
{
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
    cout << "swap02:" << *p1 << *p2 << endl;
}

int main()
{

    // 指针和函数
    // 1.值传递
    int a = 10;
    int b = 20;

    swap01(a, b); // 值传递不会改变实参
    cout << "after01:" << a << b << endl;

    // 2.地址传递
    swap02(&a, &b); // 地址传递会改变实参
    cout << "after02:" << a << b << endl;
}

/*
总结：如果不想修改实参，就是用值传递;如果想要修改实参，就是用地址传递
*/