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

  cout << "Contents of deque before erase(position) operation " << endl;
  for( auto it=d.begin() ; it != d.end() ; ++it ) {
    cout << *it << " ";
  }
  cout << endl;

  d.erase(d.begin());

  cout << "Contents of deque after erase(d.begin()) operation ";
  for( auto it=d.begin() ; it != d.end() ; ++it ) {
    cout << *it << " ";
  }
  cout << endl;

  d = {1,2,3,4,5};
  cout << "Contents of deque before erase(range) operation " << endl;
  for( auto it=d.begin() ; it != d.end() ; ++it ) {
    cout << *it << " ";
  }
  cout << endl;

  cout << "erased range using d.erase(d.begin(),d.begin()+2);" << endl;

  d.erase(d.begin(),d.begin()+2);

  cout << "Contents of deque after erase(d.begin(),d.begin()+2) operation ";
  for( auto it=d.begin() ; it != d.end() ; ++it ) {
    cout << *it << " ";
  }
  cout << endl;

  return 0;
}

