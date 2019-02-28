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
	int myint;
	char mychar;

	std::tuple<int,float,char> mytuple;

	mytuple = std::make_tuple(10,2.6,'a');

	std::tie(myint,std::ignore,mychar) = mytuple;

	std::cout << "myint contains " << myint << '\n';
	std::cout << "mychar contains " << mychar << '\n';

	return 0;
}
