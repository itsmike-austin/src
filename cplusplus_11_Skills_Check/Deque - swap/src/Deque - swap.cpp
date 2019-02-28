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
  deque<int> d2 = {50,60,70};

  cout << "Content of d1 before swap operation: ";
  for( auto it=d1.begin() ; it != d1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Content of d2 before swap operation: ";
  for( auto it=d2.begin() ; it != d2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "doing d1.swap(d2)" << endl;

  d1.swap(d2);

  cout << "Content of d1 after swap operation: ";
  for( auto it=d1.begin() ; it != d1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Content of d2 after swap operation: ";
  for( auto it=d2.begin() ; it != d2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  return 0;
}
