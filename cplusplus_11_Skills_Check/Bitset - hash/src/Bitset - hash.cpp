//============================================================================
// Name        : Bitset.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <bitset>

using namespace std;

int main()
{
  bitset<4> b1(1);
  bitset<4> b2(4);

  std::hash<std::bitset<4>> hash_fun;

  cout << "Hash function for b1 = " << hash_fun(b1) << endl;
  cout << "Hash function for b2 = " << hash_fun(b2) << endl;

  return 0;
}
