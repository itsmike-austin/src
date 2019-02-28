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
  // vector::operator equals -- copy version

  cout << "vector::operator equals -- copy version." << endl;

  vector<int> v1 = {1,2,3,4,5};
  vector<int> v2;

  cout << "Original v1: ";
  for( auto it=v1.begin() ; it != v1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original v2 size: " << v2.size() << endl;

  cout << "v2 = v1;" << endl;

  v2 = v1;

  cout << "Final v1: ";
  for( auto it=v1.begin() ; it != v1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final v2: ";
  for( auto it=v2.begin() ; it != v2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // vector::operator equals -- move version

  cout << "vector::operator equals -- move version." << endl;

  v1.clear();
  v2.clear();

  v1 = {1,2,3,4,5};

  cout << "Original v1: ";
  for( auto it=v1.begin() ; it != v1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original v2 size: " << v2.size() << endl;

  cout << "v2 = move(v1);" << endl;

  v2 = move(v1);

  cout << "Final v1: ";
  for( auto it=v1.begin() ; it != v1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final v2: ";
  for( auto it=v2.begin() ; it != v2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // vector::operator equals -- initializer list version

  cout << "vector::operator equals -- initializer list version." << endl;

  vector<int> v = {1,2,3,4,5};
  auto il = {1,2,3,4,5};

  cout << "Original v: ";
  for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original list: ";
  for( auto it=il.begin() ; it != il.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "v = il;" << endl;

  v = il;

  cout << "Final v: ";
  for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final list: ";
  for( auto it=il.begin() ; it != il.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  return 0;
}
