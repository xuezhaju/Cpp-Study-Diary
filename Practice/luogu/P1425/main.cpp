#include <bits/stdc++.h>
#include <iostream>

int main(){
	
	int a, b, c, d;

	std::cin >> a >> b >> c >> d;
	
	int f;
	int e;
	if (d < b) {
		e = c - a - 1;
		f = d + 60 - b;
	}
	else {
		e = c - a;
		f = d - b;
	}

	std::cout << e << " " << f;

	return 0;
}
