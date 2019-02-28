//============================================================================
// Name        : Set.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <set>

using namespace std;

int main()
{
  int myints[] = {50,40,30,20,10};
  set<int> myset(myints,myints+10);

  // set::begin - end

  cout << "set::begin - end " <<endl;
  cout << "for(set<int>::iterator it=s.begin() ; it != s.end() ; ++it )" << endl;
  for(set<int>::iterator it = myset.begin() ; it != myset.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // set::cbegin - cend

  cout << "set::cbegin - cend" << endl;
  cout << "for(set<int>::iterator it=s.cbegin() ; it != s.cend() ; ++it)" << endl;
  for(set<int>::iterator it = myset.cbegin() ; it != myset.cend() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // set::rbegin - rend

  cout << "set.rbegin - end" << endl;
  cout << "for(set<int>::iterator it=s.rbegin() ; it != s.rend() ; ++it )" << endl;
  for(set<int>::reverse_iterator it=myset.rbegin() ; it != myset.rend() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // set::crbegin - crend

  cout << "set.crbegin - end" << endl;
  cout << "for(set<int>::iterator it=s.crbegin() ; it != s.crend() ; ++it )" << endl;
  for(set<int>::reverse_iterator it=myset.crbegin() ; it != myset.crend() ; ++it ) cout << *it << " ";
  cout << endl;

  return 0;
}
