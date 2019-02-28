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
	std::string str("Mikeys Point...");

	for( std::string::reverse_iterator rit=str.rbegin(); rit != str.rend() ; ++rit ) {
		std::cout << *rit;
	}
	return 0;
}
