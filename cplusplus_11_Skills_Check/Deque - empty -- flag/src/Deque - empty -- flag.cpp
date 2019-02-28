//============================================================================
// Name        : Deque.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <deque>

using namespace std;

int main()
{
  deque<int> d;

  cout << "Is queue empty? " << (d.empty() ? "Yes" : "No") << endl;

  d.assign(1,1);

  cout << "Called d.assign(1,1)" << endl;

  cout << "Is queue empty? " << (d.empty() ? "Yes" : "No") << endl;

  return 0;
}
