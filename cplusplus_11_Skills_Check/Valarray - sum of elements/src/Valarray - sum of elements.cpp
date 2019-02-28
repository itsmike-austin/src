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
  int init[] = {0,10,20,30};

  std::valarray<int> myvalarray(init,4);

  std::cout << myvalarray.sum() << '\n';

  return 0;
}
