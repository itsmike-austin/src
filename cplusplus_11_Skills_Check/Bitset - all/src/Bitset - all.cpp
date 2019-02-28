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
  bitset<4> mask("1111");

  if ( !b.all() ) cout << "All bits are not set." << endl;

  b |= mask;

  if ( b.all() ) cout << "All bits are set." << endl;

  return 0;
}
