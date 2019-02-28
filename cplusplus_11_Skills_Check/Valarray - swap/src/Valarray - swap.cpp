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
  std::valarray<int> foo {0,10,20,30};
  std::valarray<int> bar {100,200,300};

  foo.swap(bar);

  std::cout << "foo contains:";
  for( auto& x : foo ) std::cout << ' ' << x;
  std::cout << '\n';

  std::cout << "bar contains:";
  for( auto& x : bar ) std::cout << ' ' << x;
  std::cout << '\n';

  return 0;
}
