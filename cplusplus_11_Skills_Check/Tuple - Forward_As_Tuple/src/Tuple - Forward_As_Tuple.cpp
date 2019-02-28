//============================================================================
// Name        : Tuple.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <tuple>
#include <string>

void print_pack( std::tuple<std::string&&,int&&> pack)
{
	std::cout << std::get<0>(pack) << ", " << std::get<1>(pack) << "\n";
}

int main() {
	std::string str("Tuple - forward_as_tuple");

	print_pack(std::forward_as_tuple(str+" somewhere nice",25));
	print_pack(std::forward_as_tuple(str+" Bopal Blew",22));
	print_pack(std::forward_as_tuple(str+" Another mess",30));
	return 0;
}
