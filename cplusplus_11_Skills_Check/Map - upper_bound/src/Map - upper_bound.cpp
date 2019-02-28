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

int main()
{

  map<char,int> m = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5},
  };

  cout << "Original map: ";
  for( auto ax=m.begin() ; ax != m.end() ;  ++ax )
	  cout << "{" << ax->first << "," << ax->second << "} ";
  cout << endl;

  cout << "it = m.upper_bound('b');" << endl;

  auto it = m.upper_bound('b');

  cout << "Upper bound is {" << it->first << "," << it->second << "}" << endl;

  return 0;
}
