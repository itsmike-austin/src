//============================================================================
// Name        : Iterator.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	vector<int> foo,bar;

	for(int i=10 ; i >= 5 ; i-- ) {
		foo.push_back(i);
		bar.push_back(i*10);
	}

	cout << "Original foo: ";
	for( auto it=foo.begin() ; it != foo.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "Original bar: ";
	for( auto it=bar.begin() ; it != bar.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "back_insert_iterator<vector<int>> back_it(foo);" << endl;
	cout << "copy(bar.begin()),bar.end(),back_it);" << endl;

	back_insert_iterator<vector<int>> back_it(foo);

	copy(bar.begin(),bar.end(),back_it);

	cout << "foo: ";
	for( vector<int>::iterator it=foo.begin() ; it != foo.end() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
