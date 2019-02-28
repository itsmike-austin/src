//============================================================================
// Name        : Array.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <array>
#include <stdexcept>

using namespace std;

int main(void)
{
  array<int,5> arr = {10,20,30,40,50};

  size_t i;

  // Print array contents

  for( i=0 ; i < arr.size() ; ++i ) cout << arr.at(i) << ' ';
  cout << endl;

  // Generate out of range exception

  try {
    arr.at(10);
  }catch( out_of_range e ) {
    cout << "out_of_range exception caught for " << e.what() << endl;
  }

  return 0;
}
