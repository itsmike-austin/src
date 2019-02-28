//============================================================================
// Name        : Bitset.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//=====
#include <iostream>
#include <bitset>

using namespace std;

int main()
{
  bitset<4> b;

  cout << "Before set operation b = " << b << endl;
  b.set(0,1);
  cout << "After b.set(0,1) operation b = " << b << endl;

  b.set();
  cout << "After b.set() operation = " << b << endl;

  b.reset();
  cout << "After b.reset() operation = " << b << endl;

  return 0;
}
