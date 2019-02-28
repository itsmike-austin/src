//============================================================================
// Name        : List.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <list>

using namespace std;

int main() {
	int p[5] = {1,2,3,4,5};
	list<int> l;

	cout << "int p[5] = {1,2,3,4,5};" << endl;
	cout << "Original array: " << endl;
	for( std::size_t i=0 ; i < (sizeof(p)/sizeof(int)) ; ++i ) cout << "p[" << i << "] = " << p[i] << endl;
	cout << endl;

	cout << "Original list: ";
	for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "l.get_allocator().allocate(5);" << endl;
	cout << "l.emplace_back(p[i]);" << endl;

	l.get_allocator().allocate(5);

	for( std::size_t i=0 ; i < (sizeof(p)/sizeof(int)) ; ++i ) l.emplace_back(p[i]);

	cout << "Final list: ";
	for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
	cout << endl << endl;

	return 0;
}
