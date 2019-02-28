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

int main() {
  unordered_map<char,int> um = {
	    {'a',1},
	    {'b',2},
	    {'c',3},
	    {'d',4},
	    {'e',5},
  };

  if ( um.count('a') == 1 ) cout << "um['a'] = " << um.at('a') << endl;

  if ( um.count('z') == 0 ) cout << "Value not present for key um['z']" << endl << endl;

  return 0;
}
