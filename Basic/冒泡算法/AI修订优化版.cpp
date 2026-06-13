#include <iostream>

using namespace std;

int main() {
    int arr[10] = {1, 5, 8, 4, 6, 9, 10, 3, 2, 7};
    
    cout << "原始数组: ";
    for(int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // 优化的冒泡排序
    bool swapped;
    for (int i = 0; i < 9; i++) {  // 需要进行9轮比较
        swapped = false;
        
        for(int j = 0; j < 9 - i; j++) {  // 每轮减少比较次数
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        
        // 如果这一轮没有交换，说明已经有序，提前结束
        if (!swapped) {
            cout << "第" << i+1 << "轮后已有序，提前结束" << endl;
            break;
        }
    }
    
    cout << "\n排序后数组: ";
    for(int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}