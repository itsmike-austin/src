//============================================================================
// Name        : Bitset.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <bitset>

using namespace std;

int main()
{
  bitset<4> b("1111");

  cout << "Before reset operation b = " << b << endl;
  b.reset();
  cout << "After reset operation b = " << b << endl;

  return 0;
}
