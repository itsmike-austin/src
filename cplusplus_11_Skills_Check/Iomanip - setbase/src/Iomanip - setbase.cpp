//============================================================================
// Name        : Iomanip.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>

int main()
{
  std::cout << std::setbase(16);
  std::cout << 110 << std::endl;

  return 0;
}
