#include <iostream>

using namespace std;

struct Student
{
    string name;
    int age;
    int score;
};

int main()
{

    // 创建学生结构体变量
    struct Student stu = {"张三", 18, 100};

    // 通过指针指向结构体变量
    struct Student *p = &stu;

    // 通过指针访问结构体变量中的数据
    // 需要利用  ->  这个符号    当然也可以通过解引用
    //  (*p).name
    cout << "姓名：" << (*p).name << "年龄：" << p->age << "分数" << p->score << endl;
    // cout << "姓名：" << p -> name << "年龄：" << p->age << "分数" << p->score << endl;
}