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

  cout << "Adding to empty deque<int>" << endl;

  for( int i=0 ; i < 5 ; ++i ) d.push_back(i+1);

  cout << "Contents after d.push_back(i+1) for [1..5]: ";
  for( std::size_t i=0 ; i < d.size() ; ++i ) cout << d[i] << " ";
  cout << endl;

  cout << "push_back: move version" << endl;
  deque<int> d1 = {1,2,3,4,5};
  deque<int> d2;

  for( std::size_t i=0 ; i < d1.size() ; ++i ) d2.push_back(move(d1[i]));
  cout << "Creating deque<int> d2 = d2.push_back(move(d1[i])): ";
  for( auto it=d2.begin() ; it != d2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  return 0;
}
