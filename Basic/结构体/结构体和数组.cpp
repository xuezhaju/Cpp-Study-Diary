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
    struct Student arr[3] =
        {
            {"ll", 18, 100},
            {"sdf", 19, 99},
            {"dsd", 18, 60}};

    // 给结构体数组中的元素赋值
    arr[2].age = 16;

    // 遍历结构体
    for (int i = 0; i < 3; i++)
    {
        cout << "姓名：" << arr[i].name << "     " << "年龄" << arr[i].age << "     " << "分数：" << arr[i].score << "     " << endl;
    }
}