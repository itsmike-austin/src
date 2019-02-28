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
  deque<int> d = {1,2,3};

  cout << "Original que: ";
  for( auto it=d.begin() ; it != d.end() ; ++it ) cout << *it << " ";
  cout << endl;

  d.emplace_back(4);
  d.emplace_back(5);

  cout << "Contents after deque.emplace_back(4), d.emplace_back(5): ";
  for( auto it=d.begin() ; it != d.end() ; ++it ) cout << *it << " ";
  cout << endl;

  return 0;
}
