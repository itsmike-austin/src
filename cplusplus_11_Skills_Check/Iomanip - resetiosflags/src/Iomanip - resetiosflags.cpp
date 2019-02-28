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
  std::cout << std::hex << std::setiosflags(std::ios::showbase);
  std::cout << 100 << std::endl;
  std::cout << std::resetiosflags(std::ios::showbase) << 100 << std::endl;

  return 0;
}
