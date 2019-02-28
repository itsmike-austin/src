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
	list<int> l1 = {1,2,3};
	list<int> l2 = {10,20,30};

	cout << "list::swap()" << endl;

	cout << "Original l1: ";
	for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "Original l2: ";
	for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "l1.swap(l2);" << endl;

	l1.swap(l2);

	cout << "Final l1: ";
	for( auto it=l1.begin() ; it != l1.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "Final l2: ";
	for( auto it=l2.begin() ; it != l2.end() ; ++it ) cout << *it << " ";
	cout << endl << endl;

	return 0;
}
