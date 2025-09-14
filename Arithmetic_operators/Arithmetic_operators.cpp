#include <iostream>
using namespace std;

double divide(int a, int b) {
    if (a == 0 || b == 0) {
        cerr << "Error: Division by zero." << endl;
        return 0; // Or handle the error as appropriate
    }
    return static_cast<double>(a) / b; //推荐
}

int main() {
    int a = 10;
    int b = 3;
    double a1 = 10.0;
    double b1 = 3.0;

    // Addition
    int sum = a + b;
    cout << "Sum: " << sum << endl;

    // Subtraction
    int difference = a - b;
    cout << "Difference: " << difference << endl;

    // Multiplication
    int product = a * b;
    cout << "Product: " << product << endl;

    // Division
    int quotient = a1 / b1;
    cout << "Quotient: " << quotient << endl;  //Dividing two integers is still an integer.

    //各种类型转换方式
    static_cast<double>(a); //C++ 风格
    double quotient2 = static_cast<double>(a) / b; //推荐
    cout << "Quotient2: " << quotient2 << endl;
    double quotient3 = (double)a / b; //C 风格
    cout << "Quotient3: " << quotient3 << endl;

    // Modulus
    int remainder = a % b;
    cout << "Remainder: " << remainder << endl;

    return 0;
}