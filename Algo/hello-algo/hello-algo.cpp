#include <cmath>
#include <iostream>

using namespace std;

int main()
{
    double x;
    cin >> x;
    double a = atan(1.00 / x) * 180 / 3.1415926535;

    cout << a << endl;
}
