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
  forward_list<int> fl = {1};

  // Single element insert_after version

  cout << "insert_after: single element version" << endl;
  cout << "fl.insert_after(fl.begin(),i+1) for insert at location." << endl;

  cout << "Original List: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl;

  for( int i=4 ; i > 0 ; --i ) fl.insert_after(fl.begin(),i+1);

  cout << "After insert_after: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // Move version of insert_after

  cout << "insert_after: move version" << endl;
  cout << "fl.insert_after(fl.begin(),move(i+1))" << endl;

  fl.clear();

  fl = {1};

  cout << "Original List: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl;

  for( int i=4 ; i > 0 ; --i ) fl.insert_after(fl.begin(),move(i+1));

  cout << "After insert_after: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // Fill version of insert_after

  fl.clear();
  fl = {1};

  cout << "insert_after: fill version" << endl;
  cout << "fl.insert_after(fl.begin(),4,1)" << endl;

  cout << "Original List: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl;

  fl.insert_after(fl.begin(),4,1);

  cout << "After insert_after: ";
  for( auto it=fl.begin() ; it != fl.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // Range version of insert_after

  forward_list<int> fl1 = {2,3,4,5};
  forward_list<int> fl2 = {1};

  cout << "insert_after: range version" << endl;
  cout << "fl2.insert_after(fl2.begin(),fl1.begin(),fl1.end())" << endl;

  cout << "fl1 Original List: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "fl2 Original List: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  fl2.insert_after(fl2.begin(),fl1.begin(),fl1.end());

  cout << "fl2 After insert_after: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // Initializer version of insert_after

  fl.clear();
  fl = {1};
  auto it = {2,3,4,5};

  cout << "insert_after: initializer version" << endl;
  cout << "it={2,3,4,5}; fl.insert_after(fl.begin(),it)" << endl;

  cout << "fl Original List: ";
  for( auto ax=fl.begin() ; ax != fl.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  cout << "it Original List: ";
  for( auto ax=it.begin() ; ax != it.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  fl.insert_after(fl.begin(),it);

  cout << "fl After insert_after: ";
  for( auto ax=fl.begin() ; ax != fl.end() ; ++ax ) cout << *ax << " ";
  cout << endl;

  return 0;
}
