#include <iostream>

using namespace std;

int main() {
    int arr[5] = {1, 3, 2, 5, 4};
    int start = 0;
    int end = sizeof(arr) / sizeof(arr[0]) - 1;  // end = 4
    
    // 修正循环：应该是 start < end
    for (; start < end ; start++) {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        end--;
    }
    
    // 修正输出循环：应该是 i < 5，不是 i <= sizeof(arr)
    cout << "逆置结果: ";
    for(int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}