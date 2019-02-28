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
	list<int> l = {1,2,3,4,5,6,7,8,9};

	cout << "List: ";
	for( auto it=l.begin() ; it != l.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "for(auto it=rbegin();it != rend() ; ++it ) cout << *it << \" \"" << endl;
	cout << "Reversed List: ";
	for( auto it=l.rbegin() ; it != l.rend() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
