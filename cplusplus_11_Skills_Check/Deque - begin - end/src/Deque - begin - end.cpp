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
  for( auto it = d.begin() ; it != d.end() ; ++it ) {
    cout << *it << " ";
  }
  cout << " using iterators begin() and end()" << endl;

  return 0;
}
