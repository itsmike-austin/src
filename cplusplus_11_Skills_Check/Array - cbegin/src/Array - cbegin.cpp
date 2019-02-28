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
  array<int,5> arr = {1,2,3,4,5};

  auto it = arr.cbegin();

  // iterate through the array

  while( it < arr.end() ) {
    cout << *it << " ";
    ++it;
  }

  cout << endl;

  return 0;
}
