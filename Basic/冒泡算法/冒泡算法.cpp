#include <iostream>

using namespace std ;

int main(){
    int arr[10] = {1, 5, 8, 4, 6, 9, 10, 3, 2, 7};
    for (int i = 10; i > 0; i --){
        
        for(int j = 0 ; j <= i; j++ ){
            int temp;
            if (arr[j] > arr[j + 1]){
                temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }

    }

    for(int i  = 0; i < 10; i++){
        cout << arr[i] << "  ";
    }

}