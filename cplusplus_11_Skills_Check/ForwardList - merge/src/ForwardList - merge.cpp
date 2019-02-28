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

bool cmp_fcn(int a,int b)
{
  return a > b;
}

int main()
{
  forward_list<int> fl1 = {1,5,11,31};
  forward_list<int> fl2 = {10,20,30};

  // Merge two sorted lists into one

  cout << "Merge two sorted lists into one." << endl;
  cout << "fl1.merge(fl2)" << endl;

  cout << "Original fl1 list: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original fl2 list: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  fl1.merge(fl2);

  cout << "Final fl1 merged list: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // Move version

  fl1.clear();
  fl2.clear();

  fl1 = {1,5,11,31};
  fl2 = {10,20,30};

  cout << "Move version." << endl;
  cout << "f1.merge(move(f2))" << endl;

  cout << "Original fl1 list: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original fl2 list: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  fl1.merge(move(fl2));

  cout << "Final fl1 list: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final fl2 list: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // Compare function

  fl1.clear();
  fl2.clear();

  fl1 = {31,11,5,1};
  fl2 = {30,20,10};

  cout << "Compare version." << endl;
  cout << "fl2.merge(fl1,cmp_fcn)" << endl;

  cout << "Original fl1: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original fl2: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  fl2.merge(fl1,cmp_fcn);

  cout << "Final fl1 list: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final fl2 list: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // Compare function move version.

  fl1.clear();
  fl2.clear();

  fl1 = {31,11,5,1};
  fl2 = {30,20,10};

  cout << "Compare function - move version" << endl;
  cout << "fl2.merge(move(fl1),cmp_fcn)" << endl;

  cout << "Original fl1: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original fl2: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  fl2.merge(move(fl1),cmp_fcn);

  cout << "Final fl1: ";
  for( auto it=fl1.begin() ; it != fl1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final fl2: ";
  for( auto it=fl2.begin() ; it != fl2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  return 0;
}

