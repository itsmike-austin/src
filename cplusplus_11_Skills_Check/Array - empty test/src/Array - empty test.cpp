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
  // Array size in zero, ti will be treated as empty array

  array<int,0>  arr1;
  array<int,10> arr2;

  if ( arr1.empty() ) {
    cout << "arr1 is empty" << endl;
  }else{
    cout << "arr1 has " << arr1.size() << " elements" << endl;
  }

  if ( arr2.empty() ) {
    cout << "arr2 is empty" << endl;
  }else{
    cout << "arr2 has " << arr2.size() << " elements " << endl;
  }

  return 0;
}
