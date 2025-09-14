#include <iostream>

using namespace std;

int main() {
    int a = 5;
    int b = 2;
    b = a++;
    ++a;
    cout << a << " " << b << endl; // 6 5
    cout << a << endl; // 6

    // 

    return 0;
}