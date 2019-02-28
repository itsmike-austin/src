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

bool comp(int a,int b)
{
  return (a > b);
}

int main()
{
  // list::sort

  list<int> l = {1,4,2,5,3};

  cout << "Original list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l.sort();" << endl;

  l.sort();

  cout << "Final list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // list::sort - compare function

  l.clear();
  l = {1,4,2,5,3};

  cout << "Original list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "l.sort(cmp_fcn); where: bool cmp_fcn(int a,int b){return (a>b);}" << endl;

  l.sort(comp);

  cout << "Final list: ";
  for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  return 0;
}
