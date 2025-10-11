#include <iostream>
#include <ctime>  //这个头文件可以加也可以不加，最新版可以不加

using namespace std ;

int main()
{
    //生成随机数要有一个种子，不然就是伪随机数，可以利用系统的当前时间作为种子进行随机数的生成
    srand( (unsigned int) time(NULL) );

    int answer = rand() % 100 + 1;  // rand() % 100 生成随机数 0～99， 在后面+1可以生成1～100
    
    int request = 0;

    while(request != answer)
    {
        cout << "请输入你心中所想的随机数：" << endl;
        cin >> request ;

        if (request > answer)
        {
            cout << "你所想的数字过大，请重新猜想～" << endl;
        }

        else if (request < answer)
        {
            cout << "你输入的数字过小，请重新猜想～" << endl ;
        }
        
        else
        {
            cout << "你猜对了，正确的答案就是" << request << ",你真幸运～"<<endl ;
        }
    }
    
    return 0 ;

}