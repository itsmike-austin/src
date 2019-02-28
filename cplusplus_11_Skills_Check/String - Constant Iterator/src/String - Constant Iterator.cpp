//============================================================================
// Name        : String.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>

int main()
{
	std::string str("Mikeys Point");

	for( auto it=str.cbegin() ; it != str.cend() ; ++it ) {
		std::cout << *it;
	}
	std::cout << '\n';

	return 0;
}
