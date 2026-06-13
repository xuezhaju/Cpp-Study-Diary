#include <iostream>

using namespace std;

int arr[5] = {1, 2, 3, 4, 5};

int main()
{
    for (int i = 0; i < 5; i++)
    {
        if( i == 2 )
        {
            arr[i] = 10;  // 修改数组中索引为2的元素
            continue;     // 跳过本次循环的剩余部分，继续下一次循环
        }
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }

    return 0;
}