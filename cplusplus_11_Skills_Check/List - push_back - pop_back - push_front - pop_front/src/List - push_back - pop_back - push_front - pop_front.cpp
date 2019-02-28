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

  // list::push_back()

  cout << "list::push_back() - basic version." << endl;

  cout << "Original list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "for(i=0;i<5;++i) l.push_back(i+1);" << endl;

  for( int i=0 ; i < 5 ; ++i ) l.push_back(i+1);

  cout << "Final list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  l.clear();

  // list::push_back() - move version

  list<int> l1 = {1,2,3,4,5};
  list<int> l2;

  cout << "list::push_back() -- move version." << endl;

  cout << "Original l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "for(it=l1.begin();it!=l1.end();++it) l2.push_back(move(*it))" << endl;
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) l2.push_back(move(*it));

  cout << "Final l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list::pop_back()

  cout << "list::pop_back()" << endl;

  l1.clear();
  l1 = {1,2,3,4,5};

  cout << "Original list: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l.pop_back();" << endl;

  l1.pop_back();

  cout << "Final list: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list::push_front()

  cout << "list::push_front();" << endl;

  cout << "for(int i=0;i<5;++i) l.push_front(i);" << endl;

  for( int i=0 ; i < 5 ; ++i ) l1.push_front(i);

  cout << "Final list: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list::pop_front()

  cout << "list::pop_front()" << endl;

  cout << "Original list: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l.pop_front(); l.pop_front();" << endl;

  l1.pop_front();
  l1.pop_front();

  cout << "Final list: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  return 0;
}
