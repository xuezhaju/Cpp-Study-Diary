#include <iostream>
using namespace std;

int main()
{
    int i = 0;

    while(i < 100)  // 改为 100，输出正好100个星号
    {

        i++;

        if(i % 10 == 0 && i != 0)  // 每10个换行（从第10个开始）
        {
            cout << "* " << endl;
        }
        else
        {
            cout << "* ";
        }
        

    }
    
    cout << endl;  // 最后换行，让提示符在下一行
    return 0;
}