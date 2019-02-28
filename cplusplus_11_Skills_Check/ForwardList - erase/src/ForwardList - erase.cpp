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
  forward_list<int> fl = {1,1000,2,3,4,5};

  cout << "Original List: ";
  for( auto ax=fl.begin() ; ax != fl.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  fl.erase_after(fl.begin());

  cout << "List after fl.erase_after(fl.begin()): ";
  for( auto ax=fl.begin() ; ax != fl.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  forward_list<int> fl1 = {1,2,3,4,5};

  cout << "Original List: ";
  for( auto ax=fl1.begin() ; ax != fl1.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  fl1.erase_after(fl1.begin(),fl1.end());

  cout << "fl1.erase_after(fl1.begin(),fl1.end()): ";
  for( auto ax=fl1.begin() ; ax != fl1.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  return 0;
}
