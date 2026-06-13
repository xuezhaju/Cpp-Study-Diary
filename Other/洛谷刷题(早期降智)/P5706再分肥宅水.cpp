#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    float cola;
    float person_cola;
    int student;
    int cup;
    
    cin >> cola >> student;

    person_cola = cola / student;
    cup = student * 2;

    cout << fixed << setprecision(3);
    cout << person_cola  << endl;
    cout << cup << endl;


}