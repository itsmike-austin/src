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

  cout << "List before insert: ";
  for( auto ax=fl.begin() ; ax != fl.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  auto it = fl.before_begin();

  fl.insert_after(it,1);

  cout << "List buit using it=f1.before_begin(); f1.insert_after(it,1);" << endl;

  cout << "List contains following elements: ";
  for( auto ax=fl.begin() ; ax != fl.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  return 0;
}
