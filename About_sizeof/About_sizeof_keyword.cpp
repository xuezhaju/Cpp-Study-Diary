// About_sizeof_keyword.cpp
#include <iostream>

int main() {
    std::cout << "Size of int: " << sizeof(int) << " bytes\n";
    std::cout << "Size of char: " << sizeof(char) << " bytes\n";
    std::cout << "Size of double: " << sizeof(double) << " bytes\n";
    std::cout << "Size of float:" << sizeof(float) << "bytes\n";
    std::cout << "Size of bool: " << sizeof(bool) << " bytes\n";
    std::cout << "Size of long: " << sizeof(long) << " bytes\n";
    std::cout << "Size of short: " << sizeof(short) << " bytes\n";
    std::cout << "Size of long long: " << sizeof(long long) << " bytes\n";
    std::cout << "Size of void*: " << sizeof(void*) << " bytes\n";
    return 0;
}