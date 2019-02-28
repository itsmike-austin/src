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

  // Print the last element

  cout << "Last element of array             = " << arr.back() << endl;

  // Modify last element

  arr.back() = 50;

  // Print modified array element

  cout << "after modification last element of array = " << arr.back() << endl;

  return 0;
}
