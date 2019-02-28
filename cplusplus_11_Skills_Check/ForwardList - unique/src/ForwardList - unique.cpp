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
  cout << "forward_list.unique() -- remove all duplicate elements." << endl;

  forward_list<int> fl = {1,1,2,2,3,4,5,5};

  cout << "Original list: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "fl.unique();" << endl;

  fl.unique();

  cout << "Final list: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  return 0;
}
