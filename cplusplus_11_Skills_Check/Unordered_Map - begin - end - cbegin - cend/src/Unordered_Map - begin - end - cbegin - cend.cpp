//============================================================================
// Name        : Unordered_Map.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main()
{
  // Unordered_Map::begin - end - container iterator

  unordered_map<char,int> um = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5},
  };

  cout << "unordered_map -- begin - end -- container iterator" << endl;

  cout << "Unordered map contains: ";
  for( auto it=um.begin() ; it != um.end() ; ++it ) {
    cout << "{"
	 << it->first
	 << ","
	 << it->second
	 << "} ";
  }
  cout << endl << endl;

  // Unordered_Map::begin - end - bucket iterator

  cout << "unordered_map -- begin - end -- bucket iterator" << endl;

  for( unsigned i=0 ; i < um.bucket_count() ; ++i ) {
    cout << "Bucket " << i << " contains:" << endl;
    for( auto it=um.begin(i) ; it != um.end(i) ; ++it ) {
      cout << it->first << " = " << it->second << endl;
    }
  }
  cout << endl;

  // Unordered_Map::cbegin - cend - container iterator

  cout << "unordered_map -- cbegin - cend -- container iterator" << endl;

  for( auto it=um.cbegin() ; it != um.cend() ; ++it )
    cout << "{" << it->first << "," << it->second << "} ";
  cout << endl << endl;

  // Unordered_Map::cbegin - cend - bucket iterator

  cout << "unordered_map -- cbegin - cend -- bucket iterator" << endl;

  for( unsigned i=0 ; i < um.bucket_count() ; ++i ) {
	  cout << "Bucket " << i << " contains:" << endl;
	  for( auto it=um.cbegin(i) ; it != um.cend(i) ; ++it ) {
		  cout << it->first << " = " << it->second << endl;
	  }
  }
  cout << endl << endl;

  return 0;
}
