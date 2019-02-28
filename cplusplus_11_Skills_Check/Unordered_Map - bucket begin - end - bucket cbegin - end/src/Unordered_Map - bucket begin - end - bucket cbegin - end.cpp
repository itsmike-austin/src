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
  // Unordered_Map::begin  -- bucket iterator

  cout << "Unordered_Map::begin - end -- bucket iterator" << endl;

  unordered_map<char,int> um = {
    {'a',1},
    {'b',2},
    {'c',3},
    {'d',4},
    {'e',5},
  };

  cout << "Unordered map contains: " << endl;

  for( unsigned int i=0 ; i < um.bucket_count() ; ++i ) {
    cout << "Bucket " << i << " contains ";

    for(unordered_map<char,int>::local_iterator it = um.begin(i) ; it != um.end(i) ; ++it ) {
      cout << "{"
	   << it->first
	   << ","
	   << it->second
	   << "} ";
    }

    cout << endl;
  }
  cout << endl << endl;

  cout << "Unordered_Map::cbegin - cend -- bucket iterator" << endl;

  cout << "Unordered map contains: " << endl;

  for( unsigned int i=0 ; i < um.bucket_count() ; ++i ) {
	  cout << "Bucket " << i << " contains ";

	  for(unordered_map<char,int>::const_local_iterator it=um.cbegin(i) ; it != um.cend(i) ; ++it ) {
		  cout << "{" << it->first << "," << it->second << "} ";
	  }
	  cout << endl;
  }

  cout << endl << endl;

  return 0;
}
