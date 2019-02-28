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
  list<int> l1 = {3,4,5};

  // list::emplace

  cout << "list::emplace" << endl;

  cout << "Original list: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "auto it = l1.emplace(l1.begin(),2);" << endl;
  cout << "l1.emplace(it,1);" << endl;

  auto it = l1.emplace(l1.begin(),2);
  l1.emplace(it,1);

  cout << "Final list: ";
  for( auto ax=l1.begin() ; ax != l1.end() ; ++ax ) cout << *ax << " ";
  cout << endl << endl;

  // list::emplace_back

  cout << "list::emplace_back" << endl;

  l1.clear();
  l1 = {1,2,3,4};

  cout << "Original list: ";
  for( auto ax=l1.begin() ; ax != l1.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  l1.emplace_back(5);

  cout << "l1.emplace_back(5);" << endl;
  for( auto ax=l1.begin() ; ax != l1.end() ; ++ax ) cout << *ax << " ";
  cout << endl << endl;


  // list::emplace_front

  cout << "list::emplace_front()" << endl;

  l1.clear();
  l1 = {2,3,4,5};

  cout << "Original list: ";
  for( auto ax=l1.begin() ; ax != l1.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  cout << "l1.emplace_front(1)" << endl;

  l1.emplace_front(1);

  cout << "Final list: ";
  for( auto ax=l1.begin() ; ax != l1.end() ; ++ax ) cout << *ax << " ";
  cout << endl << endl;

  return 0;
}
