//============================================================================
// Name        : Iterator.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iterator>
#include <list>

using namespace std;

int main() {
	list<int> alst;

	cout << "Iterator - list" << endl;

	cout << "for(i=0;i<10;++i)list.push_back(i*10);" << endl;

	for( int i=0 ; i < 10 ; i++ ) alst.push_back(i*10);

	cout << "list<int>::iterator it=list.begin();" << endl;

	list<int>::iterator it = alst.begin();

	cout << "advance(it,9);" << endl;

	advance(it,9);

	cout << "The 9th element of list is: " << *it << endl;

	cout << "Final list: ";
	for( auto it=alst.begin() ; it != alst.end() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
