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

  if ( b.none() ) cout << "All bits are unset." << endl;

  b |= mask;

  if ( !b.none() ) cout << "At least one bit is set." << endl;

  for( std::size_t i=0 ; i < b.size() ; ++i ) {
    cout << b[i] << " ";
  }
  cout << endl;

  for( std::size_t i=0 ; i < b.size() ; ++i ) if ( 1 == b[i] ) cout << "bit[" << i << "] is set!" << endl;

  return 0;
}
