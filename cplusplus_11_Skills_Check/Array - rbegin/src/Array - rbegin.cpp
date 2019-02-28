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

  // Reverse iterator points to the last element of the array

  auto rev_begin = arr.rbegin();

  // Iterator array in reverse order

  while( rev_begin < arr.rend() ) {
    cout << *rev_begin << " ";
    ++rev_begin;
  }

  cout << endl;

  return 0;
}
