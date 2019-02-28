//============================================================================
// Name        : Iterator.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	string s {"LongBiggieString"};

	cout << "Iterator - ostreambuf_iterator" << endl;

	cout << "Original string: " << s << endl;

	cout << "ostreambuf_iterator<char> out_it(cout);" << endl;
	cout << "copy(s.begin(),s.end(),out_it);" << endl;

	ostreambuf_iterator<char> out_it(cout);

	copy(s.begin(),s.end(),out_it);

	return 0;
}
