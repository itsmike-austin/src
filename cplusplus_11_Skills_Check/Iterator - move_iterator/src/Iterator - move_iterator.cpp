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

	cout << "Iterator - iterator_move" << endl;

	cout << "Original bar: ";
	for( string& x : bar ) cout << x << " ";
	cout << endl;

	typedef vector<string>::iterator Iter;

	cout << "typedef vector<string>::iterator Iter;" << endl;
	cout << "copy(move_iterator<Iter>(bar.begin()),move_iterator<Iter>(bar.end()),foo.begin());" << endl;

	copy(move_iterator<Iter>(bar.begin()),move_iterator<Iter>(bar.end()),foo.begin());

	// bar is now indeterminate

	bar.clear();

	cout << "foo: ";
	for(string& x : foo ) cout << x << " ";
	cout << endl;

	cout << "bar is now empty" << endl;

	return 0;
}
