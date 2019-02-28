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

  // We can only iterate container by using it
  // Any attempt to modify value pointed by iterator will cause compilation errors

  cout << "Using the reverse iterator\n";

  for( auto it = arr.crbegin() ; it != arr.crend() ; ++it ) {
    cout << *it << " ";
  }

  cout << '\n';

  return 0;
}
