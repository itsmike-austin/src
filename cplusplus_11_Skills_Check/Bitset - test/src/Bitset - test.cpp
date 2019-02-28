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
  bitset<4> b(1010);

  if ( b.test(1) )  cout << "b(1010):  b.test(1): " << (b.test(1) ? "true" : "false")<< endl;

  if ( !b.test(0) ) cout << "b(1010): !b.test(0): " << (!b.test(0) ? "true" : "false") << endl;

  return 0;
}
