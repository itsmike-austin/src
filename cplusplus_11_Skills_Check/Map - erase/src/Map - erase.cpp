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

  // map::erase -- position version

  cout << "map::erase -- position version." << endl;

  cout << "Original map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "map.erase(map.begin());" << endl;

  m.erase(m.begin());

  cout << "Final map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl << endl;

  // map::erase -- key version

  cout << "map::erase -- key version." << endl;

  m.clear();

  m = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5},
  };

  cout << "Original map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "map.erase(\'a\');" << endl;

  m.erase('a');

  cout << "Final map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl << endl;

  // map::erase -- range version

  cout << "map::erase -- range version." << endl;

  m.clear();

  m = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5},
  };

  cout << "Original map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl;

  cout << "auto it = m.begin(); ++it; ++it; m.erase(m.begin(),it);" << endl;

  auto it = m.begin();
  ++it;
  ++it;

  m.erase(m.begin(),it);

  cout << "Final map: ";
  for( auto it=m.begin() ; it != m.end() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl << endl;

  return 0;
}
