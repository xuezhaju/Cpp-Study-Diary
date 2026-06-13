#include <iostream>

using namespace std;

int main()
{

    // 指针和数组
    // 利用指针访问数组中的元素

    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int *p = arr; // arr就是数组的首地址

    cout << *p << endl;

    p++; // 让指针往后偏移8个字节

    cout << *p << endl;

    return 0;
}