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

  // Copy version

  cout << "Equals (=) operator: Copy version" << endl;
  cout << "fl2 = fl1" << endl;

  cout << "Original fl1 list: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original fl2 list: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  fl2 = fl1;

  cout << "Final fl1 list: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final fl2 list: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // Move version

  cout << "Equals (=) operator: Move version" << endl;
  cout << "fl2 = move(fl1)" << endl;

  fl1.clear();
  fl2.clear();

  fl1 = {1,2,3,4,5};

  cout << "Original fl1 list: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original fl2 list: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  fl2 = move(fl1);

  cout << "Final fl1 list: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final fl2 list: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // Initializer list version

  fl1.clear();
  fl2.clear();

  auto it = {1,2,3,4,5};

  cout << "Equals (=) operator: Initializer list version." << endl;
  cout << "fl1 = it where it = {1,2,3,4,5};" << endl;

  cout << "Original it list: ";
  for( auto ax=it.begin() ; ax != it.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  cout << "Original fl1 list: ";
  for( auto ax=fl1.begin() ; ax != fl1.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  fl1 = it;

  cout << "Final it list: ";
  for( auto ax=it.begin() ; ax != it.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  cout << "Final fl1 list: ";
  for( auto ax=fl1.begin() ; ax != fl1.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  return 0;
}
