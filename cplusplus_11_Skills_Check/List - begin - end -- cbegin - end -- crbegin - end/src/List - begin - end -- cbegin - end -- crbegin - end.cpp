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

  cout << "list::begin()" << endl;
  cout << "Original list using for(auto it=l.begin() ; it != l.end() ; ++it)" << endl;

  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  cout << "list::cbegin()" << endl;
  cout << "Original list using constant form: ";
  for( auto it=l.cbegin() ; it != l.cend() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  cout << "list::crbegin()" << endl;
  cout << "Original list using reverse constant form: ";
  for( auto it=l.crbegin() ; it != l.crend() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  return 0;
}

