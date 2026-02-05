#include <iostream>

using namespace std;

int main() {
    int arr[10] = {1, 5, 8, 4, 6, 9, 10, 3, 2, 7};
    
    cout << "原始数组: ";
    for(int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // 冒泡排序 - 修正版
    for (int i = 9; i > 0; i--) {  // i从9开始，不是10
        for(int j = 0; j < i; j++) {  // j < i，不是j <= i
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
        
        // 可选：显示每一轮排序结果
        cout << "第" << 10-i << "轮: ";
        for(int k = 0; k < 10; k++) {
            cout << arr[k] << " ";
        }
        cout << endl;
    }
    
    cout << "\n排序后数组: ";
    for(int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}