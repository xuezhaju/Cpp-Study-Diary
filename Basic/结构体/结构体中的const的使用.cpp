#include <iostream>

using namespace std;

struct Student
{
    string name;
    int age;
    int score;
};

// 地址传递
// 将函数中的形参改为指针，可以减少内存空间而且不会复制一个新的副本出来
void printStudentAddress(const struct Student *p)
{
    cout << "地址传递——————" << endl;
    cout << "姓名：" << p->name << endl;
    cout << "年龄：" << p->age << endl;
    cout << "分数：" << p->score << endl;
}

int main()
{
    struct Student stu = {"李彦宏", 20, 600};
    printStudentAddress(&stu);

    return 0;
}