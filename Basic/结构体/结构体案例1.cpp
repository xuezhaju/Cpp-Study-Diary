#include <iostream>
#include <string>
#include <ctime>

using namespace std;

struct Student
{
    string sName;
    int score;
};

struct Teacher
{
    string tName;
    struct Student sArray[5];
};

void allocateSpace(struct Teacher *t, int len)
{
    string nameSeed = "ABCDE";
    for (int i = 0; i < len; i++)
    {
        t[i].tName = "Teacher_" + string(1, nameSeed[i]);
        for (int j = 0; j < 5; j++)
        {
            int score = rand() % 61 + 40;
            t[i].sArray[j].sName = "Student_" + string(1, nameSeed[j]);
            t[i].sArray[j].score = score;
        }
    }
}

void printInfo(struct Teacher *t, int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << "老师的姓名：" << t[i].tName << endl;
        for (int j = 0; j < 5; j++)
        {
            cout << "\t老师的学生：" << t[i].sArray[j].sName << endl;
            cout << "\t学生的分数：" << t[i].sArray[j].score << endl;
        }

        // cout << "老师的姓名：" << t[i].tName << endl;
    }
}

int main()
{
    // 随机数种子
    srand((unsigned int)time(NULL));

    struct Teacher tArray[3];
    int len = sizeof(tArray) / sizeof(tArray[0]);
    allocateSpace(tArray, len);

    printInfo(tArray, len);

    return 0;
}