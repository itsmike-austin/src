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
  forward_list<int> fl1 = {1,2,3,4,5};
  forward_list<int> fl2;

  fl2.assign(fl1.begin(),fl1.end());

  cout << "List contains following elements: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  forward_list<int> fl3(5,10);

  cout << "List assignment using fill option: fl3(5,10)" << endl;
  cout << "List contains following elements: ";
  for( auto it=fl3.begin() ; it != fl3.end() ; ++it ) cout << *it << " ";
  cout << endl;

  auto it = {1,2,3,4,5};
  forward_list<int> f4;

  f4.assign(it);

  cout << "using assign(): f4.assign(it) where it = {1,2,3,4,5};" << endl;
  cout << "Contents of f4 after assign: ";
  for( auto ax=f4.begin() ; ax != f4.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  return 0;
}
