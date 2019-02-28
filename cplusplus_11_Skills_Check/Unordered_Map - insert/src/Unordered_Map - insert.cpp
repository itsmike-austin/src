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
	};

	cout << "Unordered_Map::insert" << endl;

	cout << "Original Unordered_Map contents: ";

	for(unordered_map<char,int>::iterator it = um.begin() ; it != um.end() ; ++it ) {
		cout << "{"
				<< it->first
				<< ","
				<< it->second
				<< "} ";
	}
	cout << endl;

	cout << "um.insert(pair<char,int>('d',4);" << endl;
	cout << "um.insert(pair<char,int>('e',5);" << endl;

	um.insert(pair<char,int>('d',4));
	um.insert(pair<char,int>('e',5));

	cout << "Final Unordered_Map contents.";

	for( auto it=um.begin() ; it != um.end() ; ++it ) {
		cout << "{"
				<< it->first
				<< ","
				<< it->second
				<< "} ";
	}
	cout << endl << endl;

	cout << "Unordered_Map::insert -- move version." << endl;

	um.erase(um.begin());

	um = {
			{'a',1},
			{'b',2},
			{'c',3},
	};

	cout << "Original Unordered_Map contents: ";

	for(unordered_map<char,int>::iterator it = um.begin() ; it != um.end() ; ++it ) {
		cout << "{"
				<< it->first
				<< ","
				<< it->second
				<< "} ";
	}
	cout << endl;

	cout << "um.insert(move(pair<char,int>('d',4)));" << endl;
	cout << "um.insert(move(pair<char,int>('e',5)));" << endl;

	um.insert(move(pair<char,int>('d',4)));
	um.insert(move(pair<char,int>('e',5)));

	cout << "Final Unordered_Map contents.";

	for( auto it=um.begin() ; it != um.end() ; ++it ) {
		cout << "{"
				<< it->first
				<< ","
				<< it->second
				<< "} ";
	}
	cout << endl << endl;

	um.erase(um.begin());

	cout << "Unordered_Map::insert - hint_version" << endl;

	um = {
			{'a',1},
			{'b',2},
			{'c',3},
	};

	cout << "Original Unordered_Map contents: ";

	for(unordered_map<char,int>::iterator it = um.begin() ; it != um.end() ; ++it ) {
		cout << "{"
				<< it->first
				<< ","
				<< it->second
				<< "} ";
	}
	cout << endl;

	cout << "um.insert(um.begin(),pair<char,int>('a',1));" << endl;
	cout << "um.insert(um.end(),pair<char,int>('e',5));" << endl;

	um.insert(um.begin(),pair<char,int>('a',1));
	um.insert(um.end(),pair<char,int>('e',5));

	cout << "Final Unordered_Map contents. ";

	for( auto it=um.begin() ; it != um.end() ; ++it ) {
		cout << "{"
				<< it->first
				<< ","
				<< it->second
				<< "} ";
	}
	cout << endl << endl;

	um.erase(um.begin());

	cout << "Unordered_Map::insert - hint and move version" << endl;

	um = {
			{'a',1},
			{'b',2},
			{'c',3},
	};

	cout << "Original Unordered_Map contents: ";

	for(unordered_map<char,int>::iterator it = um.begin() ; it != um.end() ; ++it ) {
		cout << "{"
				<< it->first
				<< ","
				<< it->second
				<< "} ";
	}
	cout << endl;

	cout << "um.insert(move(um.begin()),pair<char,int>('a',1));" << endl;
	cout << "um.insert(move(um.end()),pair<char,int>('e',5));" << endl;

	um.insert(move(um.begin()),pair<char,int>('a',1));
	um.insert(move(um.end()),pair<char,int>('e',5));

	cout << "Final unordered_map contents. ";
	for( auto it=um.begin() ; it != um.end() ; ++it ) {
		cout << "{"
				<< it->first
				<< ","
				<< it->second
				<< "} ";
	}
	cout << endl << endl;

	um.erase(um.begin());

	cout << "Unordered_Map::insert - range version" << endl;

	um = {
			{'a',1},
			{'b',2},
			{'c',3},
	};

	unordered_map<char,int> um2;

	cout << "Original Unordered_Map contents: ";

	for(unordered_map<char,int>::iterator it = um.begin() ; it != um.end() ; ++it ) {
		cout << "{"
				<< it->first
				<< ","
				<< it->second
				<< "} ";
	}
	cout << endl;

	cout << "um2.insert(um.begin(),um.end());" << endl;

	um2.insert(um.begin(),um.end());

	cout << "Final unordered_map: ";
	for( auto it=um2.begin() ; it != um2.end() ; ++it ) {
		cout << "{"
				<< it->first
				<< ","
				<< it->second
				<< "} ";
	}
	cout << endl << endl;

	um.erase(um.begin());

	cout << "Unordered_Map::insert - initializer list version" << endl;

	um = {
			{'b',2},
			{'c',3},
			{'d',4},
	};

	cout << "Original Unordered_Map contents: ";

	for(unordered_map<char,int>::iterator it = um.begin() ; it != um.end() ; ++it ) {
		cout << "{"
				<< it->first
				<< ","
				<< it->second
				<< "} ";
	}
	cout << endl;

	cout << "um.insert({{'a',1},{'e',5}});" << endl;

	um.insert({{'a',1},{'e',5}});

	cout << "Final unordered_map: ";
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
