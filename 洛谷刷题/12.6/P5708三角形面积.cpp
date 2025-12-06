#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    float p;
    float a;
    float b;
    float c;
    float s;
        
    cin >> a >> b >> c;

    p = ( a + b + c )/2;
    s = sqrt( p * ( p - a ) * ( p - b ) * ( p - c ));

    cout << fixed << setprecision(1);
    cout << s << endl;

}