//============================================================================
// Name        : List.cpp
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

  // map::begin

  cout << "map::begin();" << endl;
  cout << "for(auto it=map.begin();it != map.end();++it) cout << it->first << it->second;" << endl;

  for( auto it=m.begin() ; it != m.end() ; ++it ) cout << "{" << it->first << "," << it->second << "} ";
  cout << endl << endl;

  // map::cbegin

  cout << "map::cbegin() : constant begin map." << endl;
  cout << "for(auto it=map.cbegin();it != map.cend() ; ++it)cout << it->first << it->second;" << endl;

  for( auto it=m.cbegin() ; it != m.cend() ; ++it ) cout << "{" << it->first << "," << it->second << "} ";
  cout << endl << endl;

  // map::rbegin - reverse lookup

  cout << "map::rbegin()" << endl;
  cout << "for(auto it=map.rbegin();it != map.rend();++it) cout << it->first << it->second" << endl;

  for( auto it=m.rbegin() ; it != m.rend() ; ++it ) cout << "{" << it->first << "," << it->second << "} ";
  cout << endl << endl;

  // map::crbegin

  cout << "map::crbegin - constant reverse lookup." << endl;
  cout << "for(auto it=map.crbegin();it != map.crend();++it) cout << it->first << it->second" << endl;

  for( auto it=m.crbegin() ; it != m.crend() ; ++it ) cout << "{" << it->first << "," << it->second << "} ";
  cout << endl << endl;

  return 0;
}
