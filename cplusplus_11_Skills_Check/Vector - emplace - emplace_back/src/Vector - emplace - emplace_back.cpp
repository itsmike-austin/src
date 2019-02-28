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
  // vector::emplace

  cout << "vector::emplace(place,value)" << endl;

  vector<int> v = {1,2,5};

  cout << "Original list: ";
  for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "auto it = v.emplace(v.begin()+2,4);" << endl;

  auto it = v.emplace(v.begin()+2,4);

  cout << "Final list: ";
  for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
  cout << endl << endl;

  // vector::emplace_back

  cout << "vector::emplace_back" << endl;

  v.clear();

  v = {1,2,5};

  cout << "Original list: ";
  for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
  cout << endl;

  cout << "v.emplace_back(4);" << endl << "v.emplace_back(5);" << endl;

  v.emplace_back(4);
  v.emplace_back(5);

  cout << "Final list: ";
  for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
  cout << endl;

  return 0;
}
