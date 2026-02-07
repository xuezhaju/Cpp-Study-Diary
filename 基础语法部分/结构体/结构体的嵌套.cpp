#include <iostream>

using namespace std;

struct Student
{
    string name;
    int age;
    int score;
};

struct Teacher
{
    string name;
    int age;
    int id;
    struct Student stu;
};

int main()
{
    // 结构体嵌套结构体
    // 创建老师
    struct Teacher t{
        "老王",  // t.name
        56,      // t.age
        101114,  // t.id
        {"李斯", // t.stu.name
         18,     // t.stu.age
         100}};  // t.stu.score

    // 访问和打印
    cout << "老师信息：" << endl;
    cout << "姓名：" << t.name << endl;
    cout << "年龄：" << t.age << endl;
    cout << "工号：" << t.id << endl;

    cout << "\n学生信息：" << endl;
    cout << "姓名：" << t.stu.name << endl;
    cout << "年龄：" << t.stu.age << endl;
    cout << "分数：" << t.stu.score << endl;

    return 0;
}