#include <iostream>

using namespace std;
int main()
{
    int a = 5;
    int b = 2;
    a += b; // a = a + b
    cout << a << endl; // 7
    a -= b; // a = a - b
    cout << a << endl; // 5
    a *= b; // a = a * b
    cout << a << endl; // 10
    a /= b; // a = a / b    
    cout << a << endl; // 5
    a %= b; // a = a % b
    cout << a << endl; // 1
    return 0;
}