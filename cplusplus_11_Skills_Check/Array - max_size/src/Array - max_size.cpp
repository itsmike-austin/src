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
  array<int,10> arr;

  cout << "maximum size of arr<int,10>: " << arr.max_size() << endl;

  cout << "Size of arr:                 " << arr.size() << endl;

  return 0;
}
