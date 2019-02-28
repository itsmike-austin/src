//============================================================================
// Name        : List.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <list>

using namespace std;

int main()
{
  list<int> l = {1,2,3,4,5};

  cout << "list::back()" << endl;

  cout << "Original list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Last element of the list by l.back() is: " << l.back() << endl;

  return 0;
}
