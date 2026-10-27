#include <bits/stdc++.h>
#include <chrono>
#include <cmath>
#include <iostream>

int main(){
	int a;
	int b;
	
	std::cin >> a >> b;
	
	float c = (10 * a + b)/19;
	
	// std::cout << c;

	c = std::floor(c);
	std::cout << c;

	return 0;
}
