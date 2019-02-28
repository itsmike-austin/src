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
	list<int> l = {1,1,2,2,3,4,5,5};

	cout << "list::unique()" << endl;
	cout << "Original l: ";
	for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "l.unique();" << endl;

	l.unique();

	cout << "Final l: ";
	for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
