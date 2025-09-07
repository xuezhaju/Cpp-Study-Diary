# C++ 整型类型详解

## 目录
1. [基本整型类型](#基本整型类型)
2. [类型修饰符](#类型修饰符)
3. [取值范围](#取值范围)
4. [sizeof 操作符](#sizeof-操作符)
5. [整型字面量](#整型字面量)
6. [类型转换](#类型转换)
7. [最佳实践](#最佳实践)

## 基本整型类型

C++ 提供了几种基本的整型类型，它们的大小和取值范围可能因编译器和平台而异：

| 类型 | 说明 | 典型大小 |
|------|------|----------|
| `bool` | 布尔类型 | 1字节 |
| `char` | 字符类型 | 1字节 |
| `short` | 短整型 | 2字节 |
| `int` | 整型 | 4字节 |
| `long` | 长整型 | 4或8字节 |
| `long long` | 长长整型 | 8字节 |

## 类型修饰符

C++ 提供了类型修饰符来改变整型的符号性和大小：

### 符号性修饰符
- `signed`：有符号类型（默认）
- `unsigned`：无符号类型

### 大小修饰符
- `short`：至少16位
- `long`：至少32位
- `long long`：至少64位

## 取值范围

### 有符号整型取值范围
| 类型 | 最小值 | 最大值 |
|------|--------|--------|
| `signed char` | -128 | 127 |
| `signed short` | -32,768 | 32,767 |
| `signed int` | -2,147,483,648 | 2,147,483,647 |
| `signed long` | -2,147,483,648 | 2,147,483,647 |
| `signed long long` | -9,223,372,036,854,775,808 | 9,223,372,036,854,775,807 |

### 无符号整型取值范围
| 类型 | 最小值 | 最大值 |
|------|--------|--------|
| `unsigned char` | 0 | 255 |
| `unsigned short` | 0 | 65,535 |
| `unsigned int` | 0 | 4,294,967,295 |
| `unsigned long` | 0 | 4,294,967,295 |
| `unsigned long long` | 0 | 18,446,744,073,709,551,615 |

## sizeof 操作符

`sizeof` 操作符用于获取类型或变量的大小（以字节为单位）：

```cpp
#include <iostream>

int main() {
    std::cout << "Size of char: " << sizeof(char) << " bytes\n";
    std::cout << "Size of short: " << sizeof(short) << " bytes\n";
    std::cout << "Size of int: " << sizeof(int) << " bytes\n";
    std::cout << "Size of long: " << sizeof(long) << " bytes\n";
    std::cout << "Size of long long: " << sizeof(long long) << " bytes\n";
    
    return 0;
}