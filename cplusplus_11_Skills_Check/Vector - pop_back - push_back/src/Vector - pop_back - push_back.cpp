//============================================================================
// Name        : Vector.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
  // vector::pop_back

  cout << "vector::pop_back" << endl;

  vector<int> v = {1,2,3,4,5};

  cout << "Original v: ";
  for( unsigned i=0 ; i < v.size() ; ++i ) cout << v[i] << " ";
  cout << endl;

  cout << "v.pop_back();v.pop_back();v.pop_back();" << endl;

  v.pop_back();
  v.pop_back();
  v.pop_back();

  cout << "Final v: ";
  for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // vector::push_back

  cout << "vector::push_back" << endl;

  v.clear();

  cout << "Vector size: " << v.size() << endl;

  cout << "adding 5 elements: for(i=0;i<5;++i)v.push_back(i+1);" << endl;

  for( int i=0 ; i < 5 ; ++i ) v.push_back(i+1);

  cout << "Final vector: ";
  for( unsigned i=0 ; i < v.size() ; ++i ) cout << v[i] << " ";
  cout << endl << endl;

  return 0;
}
