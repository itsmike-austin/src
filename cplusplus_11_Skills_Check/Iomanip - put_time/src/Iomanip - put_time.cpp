//============================================================================
// Name        : Iomanip.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

int main()
{
  using std::chrono::system_clock;

  std::time_t tt = system_clock::to_time_t(system_clock::now());

  struct std::tm *ptm = std::localtime(&tt);

  std::cout << "Now (local time): " << std::put_time(ptm,"%c") << '\n';

  return 0;
}
