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
  deque<int> d = {3,4,5};

  cout << "Original que: ";
  for( auto it=d.begin() ; it != d.end() ; ++it ) cout << *it << " ";
  cout << endl;

  d.emplace_front(2);
  d.emplace_front(1);

  cout << "Contents after deque.emplace_front(2), d.emplace_front(1): ";
  for( auto it=d.begin() ; it != d.end() ; ++it ) cout << *it << " ";
  cout << endl;

  return 0;
}
