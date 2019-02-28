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
  array <int,5> arr = {1,2,3,4,5};

  // iterator pointing at the start of the array

  auto itr = arr.begin();

  // traverse complete container

  while( itr != arr.end() ) {
    cout << *itr << " ";
    ++itr;
  }

  cout << endl;

  return 0;
}
