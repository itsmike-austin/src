//============================================================================
// Name        : Utility.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <utility>
#include <iostream>
#include <tuple>
#include <vector>
#include <string>

int main()
{
  std::pair <std::string,std::vector<int>>
    foo(std::piecewise_construct,
	std::forward_as_tuple("sample"),
	std::forward_as_tuple(2,100)
	);

  std::cout << "foo.first: " << foo.first << '\n';
  std::cout << "foo.second:";
  for( int& x : foo.second ) std::cout << ' ' << x;
  std::cout << '\n';

  return 0;
}
