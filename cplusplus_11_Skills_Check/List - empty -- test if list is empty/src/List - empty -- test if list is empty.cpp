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
  list<int> l;

  // list::empty

  cout << "list::empty" << endl;

  cout << "Original list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "List is empty? " << (l.empty() ? "true" : "false") << endl;

  cout << "l.emplace_back(1);" << endl;

  l.emplace_back(1);

  cout << "List is not empty? " << (!l.empty() ? "true" : "false") << endl;

  return 0;
}
