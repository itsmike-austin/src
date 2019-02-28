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

  // list::erase -- position version

  cout << "list::erase() -- position version" << endl;

  cout << "Original list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l.erase(l.begin());" << endl;

  l.erase(l.begin());

  cout << "Final list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list::erase -- range version

  cout << "list::erase -- range version" << endl;

  l.clear();
  l = {1,2,3,4,5};

  cout << "Original list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l.erase(l.begin(),l.end());" << endl;

  l.erase(l.begin(),l.end());

  cout << "Final list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl;

  return 0;
}
