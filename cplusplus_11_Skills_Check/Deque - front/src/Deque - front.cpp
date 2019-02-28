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

  cout << "Original que: ";
  for( auto it=d.begin() ; it != d.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "First element of deque using d.front() = " << d.front() << endl;

  return 0;
}
