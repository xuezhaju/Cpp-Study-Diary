#include <iostream>

using namespace std;

void number(int num)
{

    int a = num % 10 ;
    int b = num / 10 % 10 ;
    int c = num / 100 ;

    if ( ( num < 100 ) || ( num > 999 ) )
    {
        cout << "请输入三位数..." << endl ;
    }

    else if ( ( a*a*a + b*b*b + c*c*c ) == num )
    {
       cout << "水仙花数：" << num << endl ;
    }

}

int main()
{
    int num = 100;

    while (num <= 999)
    {
        num++ ;

        number(num) ;
    }

    return 0 ;
}