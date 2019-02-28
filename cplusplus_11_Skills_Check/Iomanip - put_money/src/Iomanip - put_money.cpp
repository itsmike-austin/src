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
  std::cout << "Price:" << std::put_money(10.50L) << '\n';

  return 0;
}
