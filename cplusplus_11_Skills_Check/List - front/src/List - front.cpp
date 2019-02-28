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
	list<int> l = {1,2,3,4,5};

	cout << "List Content: ";
	for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "l.front(): " << l.front() << endl;

	return 0;
}
