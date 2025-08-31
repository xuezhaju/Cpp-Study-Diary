#include <iostream>
#include <iomanip>  // 需要包含这个头文件


//设置更长位数的数

int main() {
    double pi = 3.141592653589793;
    double e = 2.718281828459045;
    
    // 默认精度（6位）
    std::cout << "Default: " << pi << std::endl;
    
    // 设置不同精度
    std::cout << "Precision 2: " << std::setprecision(2) << pi << std::endl;
    std::cout << "Precision 4: " << std::setprecision(4) << pi << std::endl;
    std::cout << "Precision 10: " << std::setprecision(10) << pi << std::endl;
    std::cout << "Precision 15: " << std::setprecision(15) << pi << std::endl;
    
    return 0;
}