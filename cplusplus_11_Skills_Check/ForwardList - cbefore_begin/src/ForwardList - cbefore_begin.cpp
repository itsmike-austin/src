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
  forward_list<int> fl = {2,3,4,5};
  auto it = fl.cbefore_begin();

  cout << "Initial list contents: ";
  for( auto ax=fl.begin() ; ax != fl.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  fl.insert_after(it,1);

  cout << "List created as fl={2,3,4,5}; it=fl.cbefore_begin(); fl.insert_after(it,1);" << endl;

  cout << "After insert: ";
  for( auto ax=fl.begin() ; ax != fl.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  return 0;
}
