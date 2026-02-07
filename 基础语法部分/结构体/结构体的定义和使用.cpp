#include <iostream>

using namespace std;

// 1.创建学生的数据类型：学生信息包括 姓名， 年龄， 分数

struct Student
{
    // 成员列表
    string name;
    int age;
    int score;
} s3; //<=======   在创建结构体的时候顺便创建了一个结构体的变量

void printStudent(Student stu)
{
    cout << "姓名:" << stu.name
         << " 年龄:" << stu.age
         << " 分数:" << stu.score << endl;
}

int main()
{
    // 通过学生类型创建具体学生
    // 2.1 struct Student s1;
    struct Student s1;
    // 给结构体 s1赋值
    s1.age = 18;
    s1.name = "LLL";
    s1.score = 680;

    printStudent(s1);

    // 2.2 struct Student s2 = {....};
    // 给结构体 s2赋值
    struct Student s2 = {"LLLL", 19, 650};

    printStudent(s2);

    // 2.3 在创建结构体的时候顺便创建了一个结构体的变量
    s3.name = "Lao6";
    s3.age = 19;
    s3.score = 600;

    printStudent(s3);

    return 0;
}