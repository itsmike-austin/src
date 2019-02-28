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
	std::pair<int,char> foo;
	std::pair<int,int> bar;

	foo = std::make_pair(1,'a');
	bar = std::make_pair(100,3);

	std::cout << "foo: " << foo.first << ", " << foo.second << '\n';
	std::cout << "bar: " << bar.first << ", " << bar.second << '\n';
	return 0;
}
