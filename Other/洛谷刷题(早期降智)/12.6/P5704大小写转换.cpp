#include <cctype>
#include <iostream>

using namespace std;

char toggleCharCase(char input) {
    if(isupper(input)) {
        return tolower(input);

    }
    else {
        return toupper(input);

    }
    

}

int main() {
    char input;
    
    cin >> input;

    cout << toggleCharCase(input) << endl;
    
    return 0;

}