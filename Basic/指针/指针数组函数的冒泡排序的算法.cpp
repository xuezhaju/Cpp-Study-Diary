#include <iostream>

using namespace std;

/*
要求：封装一个函数，利用冒泡算法排序，实现对整形数组的升序排序
*/

void bubblsSort(int *arr, int len)
{
    /*参数1：数组的首地址
        参数2：数组的长度*/

    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printArray(int *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << endl;
    }
}

int main()
{
    // 1.先创建一个数组
    int arr[10] = {4, 3, 6, 9, 1, 2, 10, 8, 7, 5};

    int len = sizeof(arr) / sizeof(arr[0]); // 数组的长度

    // 2.创建函数实现冒泡排序

    bubblsSort(arr, len); // 数组名就是数组的首地址

    // 3.打印排序后的数组

    printArray(arr, len);

    return 0;
}
