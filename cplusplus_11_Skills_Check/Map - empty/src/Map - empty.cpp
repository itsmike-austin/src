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
  };

  // map::empty

  cout << "map::empty();" << endl;
  cout << "map.size(); = " << m.size() << endl;

  cout << "Original map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it ) cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "map.empty(); = " << (m.empty() ? "Yes" : "No") << endl;

  m.clear();

  cout << "Final map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it ) cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "map.size(); = " << m.size() << endl;

  cout << "map.empty()? " << (m.empty() ? "Yes" : "No") << endl;

  return 0;
}
