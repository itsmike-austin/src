//============================================================================
// Name        : Tuple.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <tuple>
#include <functional>

int main() {
	auto first = std::make_tuple(10,'a');

	const int a = 0;
	int   b[3];
	auto second = std::make_tuple(a,b);
	auto third  = std::make_tuple(std::ref(a),"abc");

	std::cout << "third contains: " << std::get<0>(third);
	std::cout << " and " << std::get<1>(third);
	std::cout << std::endl;

	return 0;
}
