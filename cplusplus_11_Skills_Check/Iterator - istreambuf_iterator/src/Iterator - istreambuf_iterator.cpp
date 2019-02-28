//============================================================================
// Name        : Iterator.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <vector>
#include <sstream>
#include <iostream>
#include <iterator>

using namespace std;

int main() {
	istringstream in("Hello World");

	cout << "Iterator - istreambuf_iterator" << endl;

	vector<char> v( (istreambuf_iterator<char>(in)),istreambuf_iterator<char>() );

	cout << "v has " << v.size() << " bytes. ";

	v.push_back('\0');

	cout << "it holds \"" << &v[0] << "\"\n";

	cout << "Building istringstream s(\"abc\")" << endl;
	istringstream s("abc");
	istreambuf_iterator<char> i1(s),i2(s);

	cout << "i1 returns " << *i1 << endl;
	cout << "i2 returns " << *i2 << endl;

	++i1;

	cout << "after incrementing i1, but not it\n"
			<< "i1 returns " << *i1 << endl
			<< "i2 returns " << *i2 << endl;

	++i2;

	cout << "after incrementing i2, but not i1\n"
			<< "i1 returns " << *i1 << endl
			<< "i2 returns " << *i2 << endl;

	return 0;
}
