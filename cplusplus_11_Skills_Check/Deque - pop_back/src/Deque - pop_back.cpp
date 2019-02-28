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

  cout << "Contents of deque before pop_back operation: ";
  for( std::size_t i=0 ; i < d.size() ; ++i ) cout << d[i] << " ";
  cout << endl;

  d.pop_back();
  d.pop_back();

  cout << "Contents of deque after two pop_back ops: ";
  for( std::size_t i=0 ; i < d.size() ; ++i ) cout << d[i] << " ";
  cout << endl;

  return 0;
}
