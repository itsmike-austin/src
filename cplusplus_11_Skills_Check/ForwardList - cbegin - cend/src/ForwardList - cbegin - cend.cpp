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

  cout << "List contains elements: ";
  for( auto it=fl.cbegin() ; it != fl.cend() ; ++it ) cout << *it << " ";
  cout << endl;

  return 0;
}
