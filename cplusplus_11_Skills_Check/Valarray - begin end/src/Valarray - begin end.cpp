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
  std::valarray<int> sam{0,10,20,30,40};

  std::cout << "sam contains:";

  for( auto it = begin(sam) ; it != end(sam) ; ++it ) {
    std::cout << ' ' << *it;
  }
  std::cout << '\n';

  return 0;
}
