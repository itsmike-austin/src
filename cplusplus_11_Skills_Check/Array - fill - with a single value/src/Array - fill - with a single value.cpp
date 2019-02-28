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
  int i;
  array<int,5> arr;

  for( i=0 ; i < 5 ; ++i ) arr[i] = i + 1;

  cout << "Original array" << endl;
  for( int& i : arr ) cout << i << " ";
  cout << endl;

  arr.fill(10);

  cout << "Modified array assigned 10" << endl;
  for( int& i : arr ) cout << i << " ";
  cout << endl;

  return 0;
}
