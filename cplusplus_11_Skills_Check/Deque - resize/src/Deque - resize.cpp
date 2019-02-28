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

  cout << "Initial size of deque = " << d.size() << endl;
  cout << "Resizing deque using d.resize(5)" << endl;

  d.resize(5);

  cout << "Size after resize: " << d.size() << endl;

  cout << "Contents after resize: ";
  for( auto it=d.begin() ; it != d.end() ; ++it ) cout << *it << " ";
  cout << endl;

  return 0;
}
