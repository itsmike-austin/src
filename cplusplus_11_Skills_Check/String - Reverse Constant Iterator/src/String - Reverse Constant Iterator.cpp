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

	for( auto rit=str.crbegin() ; rit != str.crend() ; ++rit ) {
		std::cout << *rit;
	}
	std::cout << "\n";

	return 0;
}
