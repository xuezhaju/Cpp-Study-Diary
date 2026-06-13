#include <iostream>

using namespace std;

/*
作用：将结构体作为参数向函数中传递
传递的方式有两种：
1.值传递
2.地址传递
*/

//////   不想修改实参用值传递，反之用地址传递   /////////

struct Student
{
    string name;
    int age;
    int score;
};

// 值传递
void printStudent(struct Student stu)
{
    cout << "姓名：" << stu.name << endl;
    cout << "年龄：" << stu.age << endl;
    cout << "分数：" << stu.score << endl;
}

// 地址传递
void printStudentAddress(struct Student *p)
{
    cout << "地址传递——————" << endl;
    cout << "姓名：" << p->name << endl;
    cout << "年龄：" << p->age << endl;
    cout << "分数：" << p->score << endl;
}

int main()
{
    struct Student stu = {"李彦宏", 20, 600};
    printStudent(stu);

    return 0;
}