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
#include <string>
#include <algorithm>

using namespace std;

int main() {
	vector<string> foo(3);
	vector<string> bar {"One","Two","Three"};

	cout << "Iterator - make_move_iterator" << endl;

	cout << "Original bar: ";
	for( string& x : bar ) cout << x << " ";
	cout << endl;

	cout << "copy(make_move_iterator(bar.begin()),make_move_iterator(bar.end()),foo.begin());" << endl;

	copy(make_move_iterator(bar.begin()),make_move_iterator(bar.end()),foo.begin());

	// bar now contains unspecified values so clear it

	bar.clear();

	cout << "bar is empty" << endl;

	cout << "Final foo: ";
	for(string& x : foo) cout << x << " ";
	cout << endl;

	return 0;
}
