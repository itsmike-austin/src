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
  deque<int> d = {1,2,3,4,5};

  cout << "Contents of deque are ";
  for( auto it=d.rbegin() ; it != d.rend() ; ++it ) cout << *it << " ";
  cout << endl;

  return 0;
}
