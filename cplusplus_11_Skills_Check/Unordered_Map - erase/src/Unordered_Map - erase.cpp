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
  // Unordered_Map::erase - position version

  cout << "Unordered_Map::erase -- position version." << endl;

  unordered_map<char,int> um = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5},
  };

  cout << "Original Unordered_Map contents." << endl;

  for( auto it=um.begin() ; it != um.end() ; ++it ) {
    cout << "{"
	 << it->first
	 << ","
	 << it->second
	 << "} ";
  }
  cout << endl;

  cout << "um.erase(um.begin());" << endl;

  um.erase(um.begin());

  cout << "Final Unordered_Map contents." << endl;

  for( auto it=um.begin() ; it != um.end() ; ++it ) {
    cout << "{"
	 << it->first
	 << ","
	 << it->second
	 << "} ";
  }
  cout << endl << endl;

  // Unordered_Map::erase - key version

  cout << "Unordered_Map::erase - key version." << endl;

  um = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5},
  };

  cout << "Original Unordered_Map contents." << endl;

  for( auto it=um.begin() ; it != um.end() ; ++it ) {
    cout << "{"
	 << it->first
	 << ","
	 << it->second
	 << "} ";
  }
  cout << endl;

  cout << "um.erase('a');" << endl;

  um.erase('a');

  cout << "Final Unordered_Map contents." << endl;

  for( auto it=um.begin() ; it != um.end() ; ++it ) {
    cout << "{"
	 << it->first
	 << ","
	 << it->second
	 << "} ";
  }

  um.erase(um.begin());

  cout << endl << endl;

  // Unordered_Map::erase - range version

  cout << "Unordered_Map::erase - range version." << endl;

  um = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5},
  };

  cout << "Original Unordered_Map contents." << endl;

  for( auto it=um.begin() ; it != um.end() ; ++it ) {
    cout << "{"
	 << it->first
	 << ","
	 << it->second
	 << "} ";
  }
  cout << endl;

  cout << "auto it = um.begin(); ++it; ++it; um.erase(um.begin(),it);" << endl;

  auto it = um.begin();
  ++it; ++it;

  um.erase(um.begin(),it);

  cout << "Final Unordered_Map contents." << endl;

  for( auto it=um.begin() ; it != um.end() ; ++it ) {
    cout << "{"
	 << it->first
	 << ","
	 << it->second
	 << "} ";
  }
  cout << endl;

  return 0;
}
