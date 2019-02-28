//============================================================================
// Name        : Tuple.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <utility>
#include <string>
#include <tuple>

int main() {
	std::tuple<float,std::string> mytuple(3.14,"pi");
	std::pair<int,char> mypair(100,'x');

	auto myauto = std::tuple_cat(mytuple,std::tuple<int,char>(mypair));

	std::cout << "myauto contains: " << '\n';
	std::cout << std::get<0>(myauto) << '\n';
	std::cout << std::get<1>(myauto) << '\n';
	std::cout << std::get<2>(myauto) << '\n';
	std::cout << std::get<3>(myauto) << '\n';

	return 0;
}
