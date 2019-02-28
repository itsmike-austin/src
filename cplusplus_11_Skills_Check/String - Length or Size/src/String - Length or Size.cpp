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
	std::string str("Once More Into The Breach");
	std::cout << str << "\n";

	unsigned sz = str.size();

	std::cout << "sz.size(): " << sz << std::endl;

	std::cout << "sz+2,+ to add two plus signs on the end of the string" << std::endl;
	str.resize(sz+2,'+');
	std::cout << str << "\n";

	str.resize(14);
	std::cout << str << '\n';

	std::cout << "Maximum size of the string: " << str.max_size() << std::endl;

	return 0;
}
