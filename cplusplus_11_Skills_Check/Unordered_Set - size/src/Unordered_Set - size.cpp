//============================================================================
// Name        : Unordered_Set.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unordered_set>

using namespace std;

int main() {
	unordered_set<string> us;

	cout << "unordered_set::size" << endl;

	cout << "0. size: " << us.size() << endl;

	us = {"a","b","c"};
	cout << "us = {\"a\",\"b\",\"c\"};" << endl;
	cout << "3. size: " << us.size() << endl;

	cout << "us.insert(\"d\");" << endl;
	us.insert("d");
	cout << "4.size: " << us.size() << endl;

	cout << "us.erase(\"a\");" << endl;
	us.erase("a");
	cout << "3.size: " << us.size() << endl;

	return 0;
}
