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
  // Unordered_Map::operator equals - copy version

  cout << "Unordered_Map::operator equals - copy version." << endl;

  unordered_map<char,int> um1 = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5}
  };

  unordered_map<char,int> um2;

  cout << "Unordered_Map 1 contains: ";
  for( auto it=um1.begin() ; it != um1.end() ; ++it ) {
    cout << "{"
	 << it->first
	 << ","
	 << it->second
	 << "} ";
  }
  cout << endl;

  cout << "um2 = um1;" << endl;

  um2 = um1;

  cout << "um2 Final contents: ";
  for( auto it=um2.begin() ; it != um2.end() ; ++it ) {
    cout << "{"
	 << it->first
	 << ","
	 << it->second
	 << "} ";
  }

  cout << endl << endl;

  um1.erase(um1.begin(),um1.end());
  um2.erase(um2.begin(),um2.end());

  // Unordered_Map::operator equals - move version

  cout << "Unordered_Map::operator equals - move version." << endl;

  um1 = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5}
  };

  cout << "um1 original contents: ";
  for( auto it=um1.begin() ; it != um1.end() ; ++it ) {
    cout << "{"
	 << it->first
	 << ","
	 << it->second
	 << "} ";
  }
  cout << endl;

  cout << "um2 = move(um1);" << endl;

  um2 = move(um1);

  cout << "um1 final contents: ";
  for( auto it=um1.begin() ; it != um1.end() ; ++it ) {
    cout << "{"
	 << it->first
	 << ","
	 << it->second
	 << "} ";
  }
  cout << endl;

  cout << "um2 final contents: ";
  for( auto it=um2.begin() ; it != um2.end() ; ++it ) {
	  cout << "{"
			  << it->first
			  << ","
			  << it->second
			  << "} ";
  }
  cout << endl << endl;

  // Unordered_Map::operator equals - initializer list version

  cout << "Unordered_Map::operator equals - initializer list version." << endl;

  cout << "unordered_map<char,int> um = { {'a',1},{'b',2},{'c',3},{'d',4} };" << endl;

  unordered_map<char,int> um = { {'a',1},{'b',2},{'c',3},{'d',4} };

  cout << "um final list: ";
  for( auto it=um.begin() ; it != um.end() ; ++it ) {
    cout << "{"
	 << it->first
	 << ","
	 << it->second
	 << "} ";
  }
  cout << endl << endl;

  return 0;
}
