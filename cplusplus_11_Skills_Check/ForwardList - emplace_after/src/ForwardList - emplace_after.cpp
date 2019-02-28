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
  forward_list<int> fl = {1,3,4,5};

  cout << "Original list: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Rebuilding list using fl.emplace_after(f1.begin(),2)" << endl;

  fl.emplace_after(fl.begin(),2);

  cout << "List after emplace: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl;

  return 0;
}
