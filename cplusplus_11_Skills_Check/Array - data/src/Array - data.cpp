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
  array<char,128> s = {"C++ standard library data"};

  char *p,*q;

  // Pointer to the first element of character array

  p = s.data();

  // Print string contents

  cout << p << endl;

  q = p;

  // Print string using pointer arithmetic

  while( *q ) {
    cout << *q;
    ++q;
  }

  cout << endl;

  return 0;
}
