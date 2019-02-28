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

  cout << "Original contents of que: ";
  for( auto ax=d.begin() ; ax != d.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  cout << "Using d.insert(d.begin(),2) and d.insert(it,1)" << endl;

  auto it = d.insert(d.begin(),2);
  d.insert(it,1);

  cout << "First insert method results: ";
  for( auto ax=d.begin() ; ax != d.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  d.insert(d.begin(),5,5);

  cout << "Insert with fill -- d.insert(d.begin(),5,5): ";
  for( auto ax=d.begin() ; ax != d.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  deque<int> d1 = {3,4,5};
  deque<int> d2 = {1,2};

  cout << "Content of que d1 are: ";
  for( auto ax=d1.begin() ; ax != d1.end() ; ++ax ) cout << *ax << " ";
  cout << endl;
  cout << "Content of que d2 are: ";
  for( auto ax=d2.begin() ; ax != d2.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  d1.insert(d1.begin(),d2.begin(),d2.end());

  cout << "Executing d1.insert(d1.begin(),d2.begin(),d2.end()): ";
  for( auto ax=d1.begin() ; ax != d1.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  deque<int> d3 = {1,2,3,4,5};
  deque<int> d4;

  cout << "d3 is {1..5}, d4 is nil. Executing d4.insert(d4.begin()+i,move(*(d1.begin()+i)));" << endl;
  for( unsigned int i=0 ; i < d3.size() ; ++i ) d4.insert(d4.begin() + i, move(*(d3.begin() + i)));

  cout << "Content after move: ";
  for( auto ax=d4.begin() ; ax != d4.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  return 0;
}
