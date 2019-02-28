//============================================================================
// Name        : Utility.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <utility>

int main() {
	int foo[4];
	int bar[] = {100,200,300,400};
	std::swap(foo,bar);

	std::cout << "foo now contains:";
	for( int i : foo ) std::cout << ' ' << i;
	std::cout << '\n';
	return 0;
}
