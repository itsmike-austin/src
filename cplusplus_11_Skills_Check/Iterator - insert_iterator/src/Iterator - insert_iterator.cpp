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
#include <algorithm>

using namespace std;

int main() {
	list<int> foo,bar;

	for( int i=10 ; i >= 5 ; i-- ) {
		foo.push_back(i);
		bar.push_back(i*10);
	}

	cout << "Original foo: ";
	for( auto it=foo.begin() ; it != foo.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "Original bar: ";
	for( auto it=bar.begin() ; it != bar.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "list<int>::iterator it = foo.begin();" << endl;
	cout << "advance(it,3);" << endl;
	cout << "insert_iterator<list<int>> insert_it(foo,it);" << endl;
	cout << "copy(bar.begin(),bar.end(),insert_it);" << endl;

	list<int>::iterator it = foo.begin();
	advance(it,3);

	insert_iterator<list<int>> insert_it(foo,it);
	copy(bar.begin(),bar.end(),insert_it);

	cout << "Final foo: ";
	for( auto it=foo.begin() ; it != foo.end() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
