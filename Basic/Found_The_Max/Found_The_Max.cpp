#include <iostream>

using namespace std;

int arr[5] = {50, 54, 54, 94, 97};

int main(){
    int max_value = arr[0];

    for(int i = 1; i < 5; i++){
        if (arr[i] > max_value){
            max_value = arr[i];
        }
    }
    cout << "Max" << max_value << endl;
    
}