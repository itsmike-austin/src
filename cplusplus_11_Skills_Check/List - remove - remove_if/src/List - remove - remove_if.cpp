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

bool foo(int n)
{
  return (n > 5);
}

int main()
{
  // list::remove

  cout << "list::remove()" << endl;

  list<int> l = {3,1,2,3,3,4,5,3};

  cout << "Original list: ";
  for(auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l.remove(3);" << endl;

  l.remove(3);

  cout << "Final list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list::remove_if

  cout << "list::remove_if()" << endl;

  l.clear();
  l = {1,2,3,4,5,6,7,8,9};

  cout << "Original list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l.remove_if(foo); where: bool foo(int n){return (n>5);}" << endl;

  l.remove_if(foo);

  cout << "Final list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  return 0;
}
