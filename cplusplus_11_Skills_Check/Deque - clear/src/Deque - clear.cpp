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

  cout << "Original contents of deque: ";
  for(auto it=d.begin() ; it != d.end() ; ++it ) {
    cout << *it << " ";
  }
  cout << endl;

  cout << "Clearing the que using deque.clear()" << endl;

  d.clear();

  cout << "Cleared contents of deque: ";
  for(auto it=d.begin() ; it != d.end() ; ++it ) {
    cout << *it << " ";
  }
  cout << endl;

  return 0;
}
