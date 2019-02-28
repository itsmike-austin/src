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
  bitset<4> b;

  cout << "b.to_string() " << b.to_string() << endl;

  b.set(0,1);
  b.set(2,1);

  cout << "b.to_ullong() " << b.to_ullong() << endl;

  cout << "Decimal Representation of " << b << " = " << b.to_ulong() << endl;

  return 0;
}
