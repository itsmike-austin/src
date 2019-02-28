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
  int init[] = {10,50,20,90};

  std::valarray<int> myvalarray(init,4);

  std::cout << "The max is " << myvalarray.max() << '\n';
  std::cout << "The min is " << myvalarray.min() << '\n';

  return 0;
}
