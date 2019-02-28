//============================================================================
// Name        : Tuple.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <tuple>

int main() {
	std::tuple<int,char> mytuple(100,'x');

	std::get<0>(mytuple) = 200;

	std::cout << "tuple contains: ";
	std::cout << std::get<0>(mytuple) << " and " << std::get<1>(mytuple);
	std::cout << std::endl;

	return 0;
}
