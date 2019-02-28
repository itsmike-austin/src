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

  // list::resize

  cout << "list::resize()" << endl;

  cout << "Original list size: " << l.size() << endl;
  cout << "l.resize(5);" << endl;
  l.resize(5);
  cout << "Final list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list::resize - value version

  cout << "list::resize - value version." << endl;

  l.clear();

  cout << "Original list size: " << l.size() << endl;
  cout << "l.resize(5,10);" << endl;

  l.resize(5,10);

  cout << "Final list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  return 0;
}
