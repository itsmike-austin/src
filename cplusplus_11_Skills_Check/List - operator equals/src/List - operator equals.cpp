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
  list<int> l1 = {1,2,3,4,5};
  list<int> l2;

  // list::operator equals - copy version

  cout << "list::operator equals - copy version." << endl;

  cout << "Original l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l2 = l1;" << endl;

  l2 = l1;

  cout << "Final l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list::operator equals - move version

  cout << "list::operator equals - move version." << endl;

  l1.clear();
  l2.clear();

  l1 = {1,2,3,4,5};

  cout << "Original l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l2 = move(l1);" << endl;

  l2 = move(l1);

  cout << "Final l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list::operator equals - initializer list version

  cout << "list::operator equals - initializer list version." << endl;

  l1.clear();
  l2.clear();

  auto it = {1,2,3,4,5};

  cout << "auto it={1,2,3,4,5}; : ";
  for( auto ax=it.begin() ; ax != it.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  cout << "l1 = it;" << endl;

  l1 = it;

  cout << "Final l1: ";
  for( auto ax=l1.begin() ; ax != l1.end() ; ++ax ) cout << *ax << " ";
  cout << endl << endl;

  return 0;
}
