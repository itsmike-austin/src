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
  // vector::assign - fill version

  vector<int> v1;

  cout << "vector::assign - fill version" << endl;

  cout << "Original size: " << v1.size() << endl;

  cout << "v1.assign(5,100);" << endl;

  v1.assign(5,100);

  cout << "Modified size = " << v1.size() << endl;

  for( unsigned i=0 ; i < v1.size() ; ++i ) cout << v1[i] << " ";
  cout << endl << endl;

  // vector::assign - range version

  cout << "vector::assign - range version" << endl;

  vector<int> v(5,100);

  cout << "Original version: " << endl;
  for( unsigned i=0 ; i < v.size() ; ++i ) cout << v[i] << " ";
  cout << endl;

  cout << "v.assign(v.begin(),v.begin()+2);" << endl;

  v.assign(v.begin(),v.begin()+2);

  cout << "Modified version: " << endl;
  for( unsigned i=0 ; i < v.size() ; ++i ) cout << v[i] << " ";
  cout << endl << endl;

  // vector::assign - initializer list version

  cout << "vector::assign initializer list version." << endl;

  vector<int> v2;

  auto il = {1,2,3,4,5};

  cout << "List contents: ";
  for( auto it = il.begin() ; it != il.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "v2.assign(il);" << endl;

  v2.assign(il);

  cout << "v2 final contents: ";
  for( unsigned i=0 ; i < v2.size() ; ++i ) cout << v2[i] << " ";
  cout << endl << endl;

  return 0;
}
