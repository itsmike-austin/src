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

  cout << "Original List: ";
  for( auto ax=fl.begin() ; ax != fl.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  cout << "f1.emplace_front(1) adds 1 to be beginning of the list." << endl;

  fl.emplace_front(1);

  cout << "List after emplace_front: ";
  for( auto ax=fl.begin() ; ax != fl.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  return 0;
}
