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
  bitset<4> mask("1010");

  if ( !b.any() ) cout << "All bits are unset." << endl;

  b |= mask;

  if ( b.any() ) cout << "bitset.any(): At least one bit is set after mask 1010." << endl;

  cout << "In bitset.count() " << b << ", " << b.count() << " bits are set." << endl;

  cout << "Before flip operation b = " << b << endl;
  b.flip();
  cout << "After flip operation b = " << b << endl;

  return 0;
}
