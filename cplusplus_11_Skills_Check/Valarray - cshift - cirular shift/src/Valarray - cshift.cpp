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

int main()
{
  int init[] = {0,10,20,30,40};

  std::valarray<int> myvalarray(init,5);

  myvalarray = myvalarray.cshift(2);
  myvalarray = myvalarray.cshift(-1);

  std::cout << "valarray contains:";

  for( std::size_t n=0 ; n < myvalarray.size() ; ++n ) {
    std::cout << ' ' << myvalarray[n];
  }

  std::cout << '\n';

  return 0;
}
