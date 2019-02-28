//============================================================================
// Name        : Iterator.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iterator>

using namespace std;

int main() {
	double value1, value2;

	cout << "Iterator - istream_iterator" << endl;

	cout << "Please insert values: ";

	cout << "istream_iterator<double> eos;\nistream_iterator<double> lit(cit);" << endl;

	istream_iterator<double> eos;
	istream_iterator<double> lit (cin);

	cout << "if ( lit != eos ) *lit;\n++lit;\nif (lit != eos ) value2 = *lit;" << endl;

	if ( lit != eos ) value1 = *lit;
	++lit;
	if ( lit != eos ) value2 = *lit;

	cout << value1 << "*" << value2 << "=" << (value1*value2) << endl;

	return 0;
}
