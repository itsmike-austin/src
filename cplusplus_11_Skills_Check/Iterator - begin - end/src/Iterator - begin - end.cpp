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

using namespace std;

int main() {
	int foo[] = {1,2,3,4,5};
	vector<int> bar;

	cout << "Iterator - begin - end" << endl;

	cout << "Contents of foo: ";
	for( auto it=begin(foo) ; it != end(foo) ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "for(it=begin(foo);it!=end(foo);++it)bar.push_back(*it);" << endl;

	for( auto it=begin(foo) ; it != end(foo) ; ++it ) bar.push_back(*it);

	cout << "Initial bar: ";
	for( auto it=bar.begin() ; it != bar.end() ; ++it ) cout << *it << " ";
	cout << endl;

	return 0;
}
