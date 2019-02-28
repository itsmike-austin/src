//============================================================================
// Name        : Unordered_Map.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
  // Unordered_Map::begin  -- container iterator

  cout << "Unordered_Map::begin - end -- container iterator" << endl;

  unordered_map<char,int> um = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5},
  };

  cout << "Unordered map contains: ";

  for(unordered_map<char,int>::iterator it = um.begin() ; it != um.end() ; ++it ) {
    cout << "{"
	 << it->first
	 << ","
	 << it->second
	 << "} ";
  }
  cout << endl << endl;

  // Unordered_Map::cbegin - cend -- container iterator

  cout << "Unordered_Map::cbegin - cend -- container iterator" << endl;

  unordered_map<char,int> umc = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5},
  };

  cout << "Unordered constant map contains: ";

  for(unordered_map<char,int>::const_iterator it = umc.cbegin() ; it != umc.cend() ; ++it ) {
    cout << "{"
	 << it->first
	 << ","
	 << it->second
	 << "} ";
  }
  cout << endl << endl;

  return 0;
}
