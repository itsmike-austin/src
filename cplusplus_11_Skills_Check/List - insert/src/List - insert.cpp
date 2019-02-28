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

  // list::insert -- single element version

  cout << "list::insert -- single element version." << endl;
  cout << "Original list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "for(i=0;i<5;++i) l.insert(l.end(),i+1);" << endl;

  for( int i=0 ; i < 5 ; ++i ) l.insert(l.end(),i+1);

  cout << "Final list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list::insert fill version

  cout << "list::insert -- fill version" << endl;

  l.clear();
  cout << "Original list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l.insert(l.begin(),5,5);" << endl;

  l.insert(l.begin(),5,5);

  cout << "Final list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list::insert -- range version

  list<int> l1 = {3,4,5};
  list<int> l2 = {1,2};

  cout << "list::insert -- range version." << endl;

  cout << "Original l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l1.insert(l1.begin(),l2.begin(),l2.end());" << endl;

  l1.insert(l1.begin(),l2.begin(),l2.end());

  cout << "Final l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list::insert -- move version

  cout << "list::insert -- move version." << endl;

  l1.clear();
  l2.clear();
  l1 = {1,2,3,4,5};

  cout << "Original l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "for(auto it=l1.begin();it!=l1.end();++it) l2.insert(l2.end(),move(*it));" << endl;
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) l2.insert(l2.end(),move(*it));

  cout << "Final l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list::insert -- initializer list version

  auto it = {1,2,3,4,5};
  l1.clear();

  cout << "list::insert -- initializer list version." << endl;

  cout << "auto it={1,2,3,4,5}; : initializer list." << endl;
  for( auto ax=it.begin() ; ax != it.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  cout << "l1.insert(l1.begin(),it);" << endl;

  l1.insert(l1.begin(),it);

  cout << "Final list: ";
  for( auto ax=l1.begin() ; ax != l1.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  return 0;
}
