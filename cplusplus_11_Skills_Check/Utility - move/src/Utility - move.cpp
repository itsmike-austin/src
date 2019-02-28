//============================================================================
// Name        : Utility.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <utility>
#include <iostream>
#include <vector>
#include <string>

int main()
{
  std::string foo = "It is a foo string";
  std::string bar = "It is a bar string";

  std::vector<std::string> myvector;

  myvector.push_back(foo);
  myvector.push_back(std::move(bar));

  std::cout << "myvector contains:";
  for( std::string& x : myvector) std::cout << ' ' << x;
  std::cout << '\n';

  return 0;
}
