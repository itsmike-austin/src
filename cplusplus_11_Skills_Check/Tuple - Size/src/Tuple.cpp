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
	std::tuple<int,int,char,double> mytuple(100,900,'a',3.14);

	std::cout << "tuple has ";
	std::cout << std::tuple_size<decltype(mytuple)>::value;
	std::cout << " elements." << "\n";

	return 0;
}
