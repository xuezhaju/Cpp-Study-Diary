#include <iostream>

using namespace std;

int main(){
    int score = 0 ; 
    cout << "请输入你的分数" << endl;
    cin >> score ;

    if ( score >= 600){
        cout << "恭喜录取重高！" << endl ;
    }

    else if (500 <= score <= 599){
        cout << "恭喜录取普高" << endl ;
    }

    else{
        cout << "滚去职高吧" << endl ;
    }
    


}