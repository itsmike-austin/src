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

  cout << "Doing push_front(i+1): i = [1..5]" << endl;

  for( int i=0 ; i < 5 ; ++i ) d.push_front(i+1);

  cout << "Contents of d after push_front: ";
  for( std::size_t i=0 ; i < d.size() ; ++i ) cout << d[i] << " ";
  cout << endl;

  cout << "push_front move version: d1.push_front(move(d[i]))" << endl;

  deque<int> d1;
  for( std::size_t i=0 ; i < d.size() ; ++i ) d1.push_front(move(d[i]));
  cout << "Contents of d1 after push-move operation: ";
  for( std::size_t i=0 ; i < d1.size() ; ++i ) cout << d1[i] << " ";
  cout << endl;

  return 0;
}
