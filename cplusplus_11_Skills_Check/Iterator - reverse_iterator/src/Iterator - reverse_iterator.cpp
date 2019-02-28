//============================================================================
// Name        : Iterator.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <iterator>

using namespace std;

int main() {
	string s = "somesongisonline";

	cout << "Iterator - reverse_iterator" << endl;

	cout << "Original string: " << s << endl;

	cout << "reverse_iterator<string::iterator> r = s.rbegin();" << endl;
	reverse_iterator<string::iterator> r = s.rbegin();

	cout << "r[10] = '0; // Change o to 0" << endl;
	r[10] = '0';
	cout << "New string: " << s << endl;

	cout << "r += 10;" << endl;
	r += 10;

	cout << "string rev(r,s.rend());" << endl;
	string rev(r,s.rend());

	cout << "reverse string: " << rev << endl;

	return 0;
}
