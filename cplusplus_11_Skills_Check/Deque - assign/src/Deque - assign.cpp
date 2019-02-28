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

  d2.assign(d1.begin(),d1.begin()+3);

  cout << "Original deque array: ";
  for( std::size_t i=0 ; i < d1.size() ; ++i ) cout << d1[i] << " ";
  cout << endl;

  cout << "Contents of d2.assign(d1.begin(),d1.begin()+3) are: ";
  for( std::size_t i=0 ; i < d2.size() ; ++i ) cout << d2[i] << " ";
  cout << endl;

  d2.assign(5,0);
  cout << "Assigned new value to d2[0]: ";
  for( std::size_t i=0 ; i < d2.size() ; ++i ) cout << d2[i] << " ";
  cout << endl;

  auto it = {9,8,7,6,5,4,3,2,1};
  d2.assign(it);
  cout << "Assigned new array to d2: ";
  for( std::size_t i=0 ; i < d2.size() ; ++i ) cout << d2[i] << " ";
  cout << endl;

  return 0;
}
