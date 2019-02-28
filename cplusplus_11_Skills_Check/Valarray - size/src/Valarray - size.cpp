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
  std::valarray<int> myvalarray;

  std::cout << "1. After construction: " << myvalarray.size() << '\n';

  myvalarray = std::valarray<int>(15);
  std::cout << "2. After assignment: " << myvalarray.size() << '\n';

  myvalarray.resize(30);
  std::cout << "3. After downsizing: " << myvalarray.size() << '\n';

  myvalarray.resize(100);
  std::cout << "4. After resizing up: " << myvalarray.size() << '\n';

  return 0;
}
