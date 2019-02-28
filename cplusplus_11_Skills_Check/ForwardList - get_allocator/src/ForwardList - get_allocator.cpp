//============================================================================
// Name        : ForwardList.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <forward_list>

using namespace std;

int main()
{
  forward_list<int> fl = {1,2,3,4,5};
  int *p = NULL;

  p = fl.get_allocator().allocate(5);

  cout << "int* p = fl.get_allocator().allocate(5)" << endl;
  cout << "Original List: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl;

  for( int i=0 ; i < 5 ; ++i ) p[i] = i+1;

  cout << "List (p) contains the following elements: ";
  for( int i=0 ; i < 5 ; ++i ) cout << p[i] << " ";
  cout << endl;

  return 0;
}
