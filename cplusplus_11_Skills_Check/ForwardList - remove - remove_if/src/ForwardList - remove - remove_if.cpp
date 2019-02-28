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

bool foo(int n)
{
  return (n > 5);
}

int main()
{
  // remove and remove_if

  forward_list<int> fl = {1,2,2,3,3,3,4,5};

  cout << "remove and remove_if." << endl;
  cout << "fl.remove(2)" << endl;

  cout << "Original list: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl;

  fl.remove(2);

  cout << "Final list: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  cout << "f1.remove_it(foo) where foo = fcn(int n) {return n>5;}" << endl;

  fl.clear();
  fl = {1,2,3,4,5,6,7,8,9};

  cout << "Original list: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl;

  fl.remove_if(foo);

  cout << "Final list: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  return 0;
}
