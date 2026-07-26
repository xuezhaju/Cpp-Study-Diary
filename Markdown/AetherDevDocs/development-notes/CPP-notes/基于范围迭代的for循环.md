# 基于范围迭代的for循环

## Sybtax
```cpp
for (declaration : expression) {
    // 循环体
}
```
- declaration 是当前范围内元素的声明，通常是一个变量定义，这个变量会依次取得 range 中每个元素的值。
- expression 是要迭代的序列，可以是花括号括起来的初始化列表、数组、容器类对象等，也可以是返回 string 字符串和容器对象的函数。

## Example
```cpp
#include <iostream>

int main() {
    int arr[] = {1, 2, 3, 4, 5};

    // 使用基于范围的 for 循环遍历数组
    for (int elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    
    // 使用基于范围的 for 循环初始化列表
    for (int elem : {6, 7, 8, 9, 10}) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
// 输出：
// 1 2 3 4 5 
// 6 7 8 9 10
```
