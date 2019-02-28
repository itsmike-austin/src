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

bool cmp_fcn(int a,int b)
{
  return ( a > b );
}

int main()
{
  // list::merge -- merge two sorted lists

  cout << "list::merge -- merge two sorted lists." << endl;

  list<int> l1 = {1,5,11,31};
  list<int> l2 = {10,20,30};

  cout << "Original l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l2.merge(l1);" << endl;

  l2.merge(l1);

  cout << "Final l2 list: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list::merge -- merge using compare function

  cout << "list::merge -- merge using compare function." << endl;

  l1.clear();
  l2.clear();

  l1 = {31,11,5,1};
  l2 = {30,20,10};

  cout << "Original l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l2.merge(l1,cmp_fcn); where cmp_fcn(a,b){return (a>b);}" << endl;

  l2.merge(l1,cmp_fcn);

  cout << "Final l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list::merge -- move version

  cout << "list::merge -- move version." << endl;

  l1.clear();
  l2.clear();

  l1 = {1,5,11,31};
  l2 = {10,20,30};

  cout << "Original l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l2.merge(move(l1));" << endl;

  cout << "Final l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list::merge -- compare function move version

  cout << "list::merge -- compare function move version." << endl;

  l1.clear();
  l2.clear();

  l1 = {31,11,5,1};
  l2 = {30,20,10};

  cout << "Original l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l2.merge(move(l1),cmp_fcn);" << endl;

  l2.merge(move(l1),cmp_fcn);

  cout << "Final l1: ";
  for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final l2: ";
  for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  return 0;
}
