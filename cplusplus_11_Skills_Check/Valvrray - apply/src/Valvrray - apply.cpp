//============================================================================
// Name        : Valvrray.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstddef>
#include <valarray>

int increment (int x) { return ++x; }

int main()
{
  int init[] = {0,10,20,30,40};

  std::valarray<int> foo(init,5);
  std::valarray<int> bar = foo.apply(increment);

  std::cout << "foo contains:";

  for( std::size_t n=0 ; n < bar.size() ; ++n ) {
    std::cout << ' ' << bar[n];
  }

  std::cout << '\n';

  return 0;
 }
