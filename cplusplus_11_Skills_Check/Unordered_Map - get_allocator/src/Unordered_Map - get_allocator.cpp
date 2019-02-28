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
	unordered_map<char,int> um;
	pair<const char,int>   *p;

	cout << "Unordered_Map::get_allocator()" << endl;

	cout << "p = um.get_allocator().allocate(5);" << endl;

	p = um.get_allocator().allocate(5);

	cout << "Allocated size = " << sizeof(*p) * 5 << endl << endl;
	return 0;
}
