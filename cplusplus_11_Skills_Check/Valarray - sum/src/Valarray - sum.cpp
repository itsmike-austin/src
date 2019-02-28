//============================================================================
// Name        : Valarray.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <valarray>

int main()
{
  std::valarray<int> foo(10);
  std::valarray<int> bar(2,40);

  foo = bar;
  bar = 5;
  foo = bar[std::slice(0,4,1)];

  std::cout << "foo sums " << foo.sum() << '\n';

  std::cout << "foo contents:";
  for(int& i : foo) std::cout << ' ' << i;
  std::cout << std::endl;

  return 0;
}
