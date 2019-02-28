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

  // Print first element

  cout << "First element of array                  " << arr.front() << endl;

  // Modify value

  arr.front() = 1;

  // Print modified value

  cout << "After modification first element of array = " << arr.front() << endl;

  return 0;
}
