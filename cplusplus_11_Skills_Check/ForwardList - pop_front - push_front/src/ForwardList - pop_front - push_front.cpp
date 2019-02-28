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

int main()
{
  // Push and pop front

  cout << "Push and pop front." << endl;
  cout << "fl.pop_front()" << endl;

  forward_list<int> fl = {1,2,3,4,5};

  cout << "Original list: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "fl.pop_front(); fl.pop_front();" << endl;

  fl.pop_front();
  fl.pop_front();

  cout << "Final list: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // push_front copy version

  cout << "push_front() copy version." << endl;
  cout << "for(i=0;i<5;++i) fl.push_front(i+1);" << endl;

  fl.clear();

  for( int i=0 ; i < 5 ; ++i ) fl.push_front(i+1);

  cout << "Final list: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // push_front move version

  forward_list<int> fl1 = {1,2,3,4,5};
  forward_list<int> fl2;

  cout << "push_front() move version." << endl;
  cout << "for(begin;end;++it) { fl2.push_front(move(*it));" << endl;

  cout << "Original list: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) fl2.push_front(move(*it));

  cout << "final list: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  return 0;
}
