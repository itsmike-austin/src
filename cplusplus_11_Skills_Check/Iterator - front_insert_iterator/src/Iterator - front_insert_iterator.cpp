//============================================================================
// Name        : Iterator.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iterator>
#include <deque>
#include <algorithm>

using namespace std;

int main() {
	deque<int> foo,bar;

	cout << "Iterator - front_iterator_insert" << endl;

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

	cout << "front_insert_iterator<deque<int>> front_it(foo);" << endl;
	cout << "copy(bar.begin(),bar.end(),front_it);" << endl;

	front_insert_iterator<deque<int>> front_it(foo);

	copy(bar.begin(),bar.end(),front_it);

	cout << "Final foo: ";
	for( auto it=foo.begin() ; it != foo.end() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
