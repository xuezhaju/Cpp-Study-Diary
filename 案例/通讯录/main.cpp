#include <iostream>

#define MAX 1000

using namespace std;

// 联系人的结构体
struct Person
{
    string m_Name;
    int m_Sex; // 1 man  2woman
    int m_Age;
    string m_Phone;
    string m_Addr;
};

struct Addressbooks
{
    struct Person personArray[MAX];
    int m_Size;
};

void showMenu()
{
    cout << "================" << endl;
    cout << "==1.添加联系人==" << endl;
    cout << "==2.显示联系人==" << endl;
    cout << "==3.删除联系人==" << endl;
    cout << "==4.查找联系人==" << endl;
    cout << "==5.修改联系人==" << endl;
    cout << "==6.清空联系人==" << endl;
    cout << "==0.退出联系人==" << endl;
    cout << "================" << endl;
}

int main()
{
    int selcet = 0; // 用户选择输入的变量

    while (true)
    {

        cin >> selcet;
        switch (selcet)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 0:
            cout << "欢迎再次使用" << endl;
            return 0;

        default:
            break;
        }
        showMenu();
    }

    return 0;
}