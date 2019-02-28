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

  // list assign -- range version

  cout << "list::assign -- range version" << endl;

  cout << "Original l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l2.assign(l1.begin(),l1.end());" << endl;

  l2.assign(l1.begin(),l1.end());

  cout << "Final l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list assign -- fill version

  cout << "list::assign -- fill version" << endl;

  l1.clear();

  cout << "Initial list: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l1.assign(5,10);" << endl;

  l1.assign(5,10);

  cout << "Final l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list assign -- initializer list version

  cout << "list::assign -- initializer list version" << endl;

  l1.clear();

  auto it = {1,2,3,4,5};

  cout << "Original auto it={1,2,3,4,5};" << endl;
  for( auto ax=it.begin() ; ax != it.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  cout << "Original l1: ";
  for( auto ax=l1.begin() ; ax != l1.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  cout << "l1.assign(it);" << endl;

  cout << "Final l1: ";
  for( auto ax=l1.begin() ; ax != l1.end() ; ++ax ) cout << *ax << " ";
  cout << endl << endl;

  return 0;
}

