#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

void spend(int speed, int lucheng)
{
    int time = lucheng / speed;
    int hour = time / 60;
    int minutes = time % 60;
    int st_hour;
    int st_minutes;

    if (hour <= 8)
    {
        st_hour = 8 - hour;
        st_minutes = 60 - minutes;
    }
    else
    {
        st_hour = 12 - (hour - 8);
        st_minutes = 60 - minutes;
    }

    if ((st_hour < 10) and (st_hour < 10))
    {
        cout << "0" << to_string(hour) << ":" << "0" << to_string(st_minutes);
    }
    else if ((st_hour < 10) and (st_hour > 10))
    {
        cout << "0" << to_string(hour) << ":" << to_string(st_minutes);
    }
    else if (((st_hour > 10) and (st_hour < 10)))
    {
        cout << to_string(hour) << ":" << "0" << to_string(st_minutes);
    }
    else if (((st_hour > 10) and (st_hour > 10)))
    {
        cout << to_string(hour) << ":" << to_string(st_minutes);
    }
}

int main()
{
    int s;
    int v;
    cin >> s >> v;

    spend(v, s);

    return 0;
}