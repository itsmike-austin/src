//============================================================================
// Name        : Utility.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <utility>
#include <iostream>

void overloaded (const int& x) { std::cout << "[It is a lvalue]"; }
void overloaded (int&& x)      { std::cout << "[It is a rvalue]"; }

template <class T> void fn (T&& x) {
	overloaded(x);
	overloaded(std::forward<T>(x));
}

int main() {
	int a;

	std::cout << "calling fn with lvalue: ";
	fn(a);
	std::cout << '\n';

	std::cout << "calling fn with rvalue: ";
	fn(0);
	std::cout << '\n';
	return 0;
}
