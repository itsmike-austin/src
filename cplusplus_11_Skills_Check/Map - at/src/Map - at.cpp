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

int main() {

	map<char,int> m = {
			{'a',1},
			{'b',2},
			{'c',3},
			{'d',4},
			{'e',5},
	};

	cout << "Original map: ";
	for( auto it=m.begin() ; it != m.end() ; ++it ) cout << "{" << it->first << " = " << it->second << "}" << " ";
	cout << endl;

	cout << "Value of key at [\'a\'] = " << m.at('a') << endl;

	try {
		cout << "trying m.at(\'z\');" << endl;
		m.at('z');
	}catch( const out_of_range &e) {
		cerr << "Exception at " << e.what() << endl;
	}

	return 0;
}
