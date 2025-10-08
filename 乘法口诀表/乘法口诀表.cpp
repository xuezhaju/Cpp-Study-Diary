#include <iostream>
#include <iomanip>  // 用于格式化输出
using namespace std;

int main()
{
    for(int i = 1; i < 10; i++)
    {
        for(int j = 1; (j < 10) && (i >= j); j++)
        {
            cout << i << "×" << j << "=" << setw(2) << i*j;
            
            if(j < 9)
                cout << "  ";  // 列之间空格
        }
        cout << endl;  // 每行结束换行
    }
    
    return 0;
}