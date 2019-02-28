//============================================================================
// Name        : Map.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <map>

using namespace std;

int main() {
  map<char,int> m1 = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5},
  };

  map<char,int> m2;

  cout << "Original map1: ";
  for(auto it=m1.begin() ; it != m1.end() ; ++it )
	  cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "Original map2: ";
  for(auto it=m2.begin() ; it != m2.end() ; ++it )
	  cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "m1.swap(m2);" << endl;

  m1.swap(m2);

  cout << "Final map1: ";
  for(auto it=m1.begin() ; it != m1.end() ; ++it )
	  cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "Final map2: ";
  for(auto it=m2.begin() ; it != m2.end() ; ++it )
	  cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  return 0;
}
