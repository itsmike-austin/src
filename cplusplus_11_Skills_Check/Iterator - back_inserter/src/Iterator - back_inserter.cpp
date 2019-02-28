//============================================================================
// Name        : Iterator.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

int main() {
	vector<int> foo,bar;

	cout << "Iterator - back_inserter" << endl;

	cout << "Inserting data into foo and bar" << endl;

	for( int i=1 ; i < 3 ; ++i ) {
		foo.push_back(i);
		bar.push_back(i+10);
	}

	cout << "Original foo: ";
	for( auto it=foo.begin() ; it != foo.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "Original bar: ";
	for( auto it=bar.begin() ; it != bar.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "copy(bar.begin(),bar.end(),back_inserter(foo));" << endl;

	copy(bar.begin(),bar.end(),back_inserter(foo));

	cout << "Final foo: ";
	for( auto it=foo.begin() ; it != foo.end() ; ++ it ) cout << *it << " ";
	cout << endl;

	cout << "Final bar: ";
	for( auto it=bar.begin() ; it != bar.end() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
