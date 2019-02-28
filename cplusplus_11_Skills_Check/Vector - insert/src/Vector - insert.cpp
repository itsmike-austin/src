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
  // vector::insert -- single element version

  cout << "vector::insert -- single element version." << endl;

  vector<int> v = {3,4,5};

  cout << "Original vector: ";
  for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "executing it=v.insert(v.begin(),2);v.insert(it,1);" << endl;

  auto it = v.insert(v.begin(),2);
  v.insert(it,1);

  cout << "Final vector: ";
  for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // vector::insert -- fill version

  cout << "vector::insert -- fill version." << endl;

  v.clear();
  v = {5};

  cout << "Original vector: ";
  for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "executing v.insert(v.begin(),4,5);" << endl;
  v.insert(v.begin(),4,5);

  cout << "Final vector: ";
  for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // vector::insert -- range version

  cout << "vector::insert -- range version." << endl;

  vector<int> v1 = {2,3,4,5};
  vector<int> v2 = {1};

  cout << "Original v1: ";
  for( auto it=v1.begin() ; it != v1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Original v2: ";
  for( auto it=v2.begin() ; it != v2.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "executing v2.insert(v2.begin()+1,v1.begin(),v1.begin()+3);" << endl;

  v2.insert(v2.begin()+1,v1.begin(),v1.begin()+3);

  cout << "Final v2: ";
  for( auto it=v2.begin() ; it != v2.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // vector::insert -- move version

  cout << "vector::insert -- move version." << endl;

  v1.clear();
  v2.clear();

  v1 = {1,2,3,4,5};

  cout << "Original v1: ";
  for( auto it=v1.begin() ; it != v1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "executing for(i=0;i<v1.size();++i) v2.insert(v2.begin()+i,move(*(v1.begin()+1)));" << endl;

  for( unsigned i=0 ; i < v1.size() ; ++i ) {
    v2.insert(v2.begin()+i,move(*(v1.begin()+i)));
  }

  cout << "Final v1: ";
  for( auto it=v1.begin() ; it != v1.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Final v2: ";
  for( auto it=v2.begin() ; it != v2.end() ;  ++it ) cout << *it << " ";
  cout << endl << endl;

  // vector::insert -- initializer list version

  cout << "vector::insert -- intializer list version." << endl;

  v.clear();

  v = {1,2};
  auto il = {3,4,5};

  cout << "Original vector: ";
  for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "List contents: ";
  for( auto it=il.begin() ; it != il.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "executing v.insert(v.begin()+2,il);" << endl;

  v.insert(v.begin()+2,il);

  cout << "Final vector: ";
  for( unsigned i=0 ; i < v.size() ; ++i ) cout << v[i] << " ";
  cout << endl << endl;

  return 0;
}
