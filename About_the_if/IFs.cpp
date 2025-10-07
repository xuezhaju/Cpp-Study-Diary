#include <iostream>

using namespace std;

int main(){
    int score = 0 ; 
    cout << "请输入你的分数" << "你的分数是" << score << endl;
    cin >> score ;

    if ( score >= 600){
        cout << "恭喜录取重高！" << "你的分数是" << score <<  endl ;
    }

    else if (500 <= score <= 599){
        cout << "恭喜录取普高" << "你的分数是" << score << endl ;
    }

    else{
        cout << "滚去职高吧" << "你的分数是" << score << endl ;
    }
    


}