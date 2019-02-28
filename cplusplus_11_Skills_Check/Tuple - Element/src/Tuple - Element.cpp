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
	auto mytuple = std::make_tuple(100,'x');

	std::tuple_element<0,decltype(mytuple)>::type first  = std::get<0>(mytuple);
	std::tuple_element<1,decltype(mytuple)>::type second = std::get<1>(mytuple);

	std::cout << "First Item: " << first << '\n';
	std::cout << "Second Item: " << second << '\n';

	return 0;
}
