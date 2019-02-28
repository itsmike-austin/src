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
  deque<int> d {1,2,3,4,5};

  cout << "deque<int> d {1,2,3,4,5};" << endl;

  cout << "Contents of deque using d[i] in for loop: ";
  for( std::size_t i=0 ; i < d.size() ; ++i ) cout << d[i] << " ";
  cout << endl;

  return 0;
}
