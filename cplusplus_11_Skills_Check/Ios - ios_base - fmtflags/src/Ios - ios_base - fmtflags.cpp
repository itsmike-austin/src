//============================================================================
// Name        : Ios.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

int main()
{
  std::cout.setf(std::ios_base::hex,std::ios_base::basefield);
  std::cout.setf(std::ios_base::showbase);
  std::cout << 100 << '\n';

  std::cout.setf(std::ios::hex,std::ios::basefield);
  std::cout.setf(std::ios::showbase);
  std::cout << 100 << '\n';

  std::cout.setf(std::cout.hex,std::cout.basefield);
  std::cout.setf(std::cout.showbase);
  std::cout << 100 << '\n';

  std::ios_base::fmtflags ff;
  ff = std::cout.flags();
  ff &= ~std::cout.basefield;
  ff |= std::cout.hex;
  ff |= std::cout.showbase;

  std::cout.flags(ff);
  std::cout << 100 << '\n';

  std::cout << std::hex << std::showbase << 100 << '\n';

  return 0;
}
