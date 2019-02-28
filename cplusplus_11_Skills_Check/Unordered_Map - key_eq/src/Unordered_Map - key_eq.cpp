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
	unordered_map<string,string> um;

	cout << "Unordered_Map::key_eq" << endl;

	cout << "bool case_insensitive = um.key_eq()(\"jerry\",\"JERRY\");" << endl;

	bool case_insensitive = um.key_eq()("jerry","JERRY");

	cout << "mymap_key.eq() is ";
	cout << (case_insensitive ? "case_insensitive" : "case_sensitive");
	cout << endl;

	return 0;
}
