### Input Of Data

#### The Keyword
- cin >>

#### Grammar
    #include <iostream>

    using namespace std;

    int main() {
        int a = 0;   ///First create a variable
        cout << "Input of data" << endl;    //Then display prompt message
        cin >> a;     // Third,get user inputed
        cout << a << endl;    // Finally, output the received value
    }