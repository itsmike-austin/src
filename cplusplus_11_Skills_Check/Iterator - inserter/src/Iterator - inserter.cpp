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

	cout << "Iterator - inserter" << endl;

	for( int i=1 ; i <= 5 ; ++i ) {
		foo.push_back(i);
		bar.push_back(i*10);
	}

	cout << "Original foo: ";
	for( auto it=foo.begin() ; it != foo.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "Original bar: ";
	for( auto it=bar.begin() ; it != bar.end() ; ++it ) cout << *it << " ";
	cout << endl;

	list<int>::iterator it = foo.begin();

	cout << "foo - advance(it,3); where it=list<int>::iterator" << endl;

	advance(it,3);

	cout << "copy(bar.begin(),bar.end(),inserter(foo,it));" << endl;

	copy(bar.begin(),bar.end(),inserter(foo,it));

	cout << "Final foo: ";
	for( auto ax=foo.begin() ; ax != foo.end() ; ++ax ) cout << *ax << " ";
	cout << endl;

	cout << "Final bar: ";
	for( auto ax=bar.begin() ; ax != bar.end() ; ++ax ) cout << *ax << " ";
	cout << endl;

	return 0;
}
