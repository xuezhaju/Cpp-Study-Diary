#include <iostream>

/*
3.14      // double 类型（默认）
3.14f     // float 类型
3.14F     // float 类型（大写F也可以）
3.14l     // long double 类型
3.14L     // long double 类型

不做配置默认只能显示6位有效数字
*/


int main() {
    float f = 3.14f; // 加上“f”可以告诉编辑器这是一个float类型，减少一步转换的过程，增加效率
    double d = 3.14; //没有后缀表示双精度字面值

    std::cout << "Size of float: " << sizeof(f) << " bytes" << std::endl;
    std::cout << "Size of double: " << sizeof(d) << " bytes" << std::endl;

    std::cout << "Value of float: " << f << std::endl;
    std::cout << "Value of double: " << d << std::endl;

    return 0;
}