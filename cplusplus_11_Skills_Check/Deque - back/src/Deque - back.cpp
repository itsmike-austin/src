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

  cout << "Original queue: ";
  for( std::size_t i=0 ; i < d.size() ; ++i ) cout << d.at(i) << " ";
  cout << endl;

  cout << "Last element of deque = " << d.back() << endl;

  return 0;
}
