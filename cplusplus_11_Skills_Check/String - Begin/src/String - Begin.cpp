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
	std::string str("Tutorial String");

	for( std::string::iterator it=str.begin() ; it != str.end() ; ++it ) {
		std::cout << *it;
	}

	std::cout << "\n";

	return 0;
}
