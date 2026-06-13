#include <algorithm>
#include <iostream>

using namespace std;


int main() {
    string num;

    cin >> num ; 

    reverse(num.begin(), num.end());

    cout << num << endl;


}