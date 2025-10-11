#include <iostream>

using namespace std;

int main(){

    int a = 10;
    int b = 6;
    int c = 0;

    // b >= a ? c = b : c = a ;

    c = (b >= a ? b : a );  //更好的写法

    cout << c << endl ;
    
    return 0 ;

}