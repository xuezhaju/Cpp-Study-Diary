#include <algorithm>
#include <bits/stdc++.h>
#include <cmath>
#include <iostream>

int h;
int r;

int result;

float pi = 3.14;

int main(){
	std::cin >> h >> r;
	
	// std::cout << h << r;

	double v = pi * pow(r, 2) * h;
	
	// std::cout << v;
		
	result = ceil(20000 / v);

	std::cout << result;

	return result;
}
