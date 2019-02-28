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
  deque<int> d1 = {1,2,3,4,5};
  deque<int> d2;
  deque<int> d3;

  cout << "d1.size = " << d1.size() << endl;
  cout << "d1 contents: ";
  for( auto it=d1.begin() ; it != d1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "d2.size = " << d2.size() << endl;

  cout << "d2 = d1" << endl;

  d2 = d1;

  cout << "d2.size = " << d2.size() << endl;
  cout << "Contents of d2 are: ";
  for( auto it=d2.begin() ; it != d2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  d3 = move(d2);

  cout << "d3 = move(d2)" << endl;
  cout << "d2.size = " << d2.size() << endl;
  cout << "d3.size = " << d3.size() << endl;

  cout << "Contents of d3 are: ";
  for( auto it=d3.begin() ; it != d3.end() ; ++it ) cout << *it << " ";
  cout << endl;

  auto arr = {1,2,3,4,5};
  deque<int> d5;

  d5 = arr;
  cout << "deque<int> d5 = arr[1..5]" << endl;
  cout << "Contents of d5 are: ";
  for( auto it=d5.begin() ; it != d5.end() ; ++it ) cout << *it << " ";
  cout << endl;

  return 0;
}
