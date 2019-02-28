//============================================================================
// Name        : Array.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <array>

using namespace std;

int main()
{
  array<int,5> arr = {10,20,30,40,50};

  // Iterator pointing at the start of the array

  auto start = arr.begin();

  // Iterator pointing past the end of array

  auto end = arr.end();

  // Iterate complete array

  while( start < end ) {
    cout << *start << " ";
    ++start;
  }

  cout << endl;

  return 0;
}
