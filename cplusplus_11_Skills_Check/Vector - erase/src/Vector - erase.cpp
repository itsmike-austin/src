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
  // vector::empty -- position version

  cout << "vector::empty -- position version" << endl;

  vector<int> v = {1,2,3,4,5};

  cout << "Original vector: ";
  for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Remove first element using v.erase(v.begin());" << endl;

  v.erase(v.begin());

  cout << "Modified vector: ";
  for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // vector::empty -- range version

  cout << "vector::empty -- range version" << endl;

  v.clear();

  v = {1,2,3,4,5};

  cout << "Original vector: ";
  for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "Remove first two elements using v.erase(v.begin(),v.begin()+1);" << endl;
  v.erase(v.begin(),v.begin()+2);

  cout << "Modified vector: ";
  for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
  cout << endl;

  return 0;
}
