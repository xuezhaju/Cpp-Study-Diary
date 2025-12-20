#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

string turn_minu_to_h(int total_minutes) {
    float h = total_minutes / 60.0;
    int m = total_minutes % 60;
 
    string hour_str = (h < 10) ? "0" + to_string( int(8 - ceil(h)) ) : to_string( int(8 - ceil(h)) );
    string minute_str = (m < 10) ? "0" + to_string( 60 - m ) : to_string( 60 - m );
    
    return hour_str + ":" + minute_str;
}

int main() {
    float s, v;
    cin >> s >> v;
 
    int total_minutes = ceil(s / v);

    total_minutes += 10;

    string time_str = turn_minu_to_h(total_minutes);
    cout << time_str << endl;
    
    return 0;
}