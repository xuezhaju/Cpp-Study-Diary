#include <iostream>

using namespace std;

int main() {
    // 前置递增和后置递增的区别
    // 前置递增（++a）：先将变量的值加1，然后再使用该变量
    int a = 5;
    int b = 2;
    b = b + ++a;
    ++a;
    cout << a << " " << b << endl; 
    cout << a << endl;

    // 后置递增（a++）：先使用变量的当前值，然后再将变量的值加1
    int a1 = 5;
    int b1 = 2;
    b1 = b1 * a1++;
    ++a1;
    cout << a1 << " " << b1 << endl; 
    cout << a1 << endl;

    return 0;
}