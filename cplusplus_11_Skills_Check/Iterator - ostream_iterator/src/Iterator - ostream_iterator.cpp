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
	vector<int> v;

	cout << "Iterator - ostream_iterator" << endl;

	for( int i=10 ; i > 1 ; i-- ) v.push_back(i*10);

	cout << "Original v: ";
	for( auto it=v.begin() ; it != v.end() ; ++it ) cout << *it << " ";
	cout << endl;

	cout << "ostream_iterator<int> out_it(cout,\", \");" << endl;
	cout << "copy(v.begin(),v.end(),out_id);" << endl;

	cout << "copy executes iterator." << endl;

	ostream_iterator<int> out_it(cout,", ");

	copy(v.begin(),v.end(),out_it);

	return 0;
}
