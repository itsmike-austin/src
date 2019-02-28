//============================================================================
// Name        : Valarray.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstddef>
#include <valarray>

int increment(int x) {return ++x;}

int main()
{
  std::valarray<int> myarray(100,50);

  myarray.resize(3);

  std::cout << "myvalarray contains:";

  for( std::size_t n=0 ; n < myarray.size() ; ++n ) {
    std::cout << ' ' << myarray[n];
  }

  std::cout << '\n';

  return 0;
}
