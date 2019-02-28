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
  std::cout << std::hex;

  std::cout << std::setiosflags(std::ios::showbase|std::ios::uppercase);
  std::cout << 100 << std::endl;

  return 0;
}
