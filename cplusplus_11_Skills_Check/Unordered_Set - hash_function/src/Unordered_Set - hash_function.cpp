//============================================================================
// Name        : Unordered_Set.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
	unordered_set<string> us;
	unordered_set<string>::hasher fn = us.hash_function();

	cout << "Unordered_Set - hash_function" << endl;

	cout << "unordered_set<string>::hasher fn = us.hash_function();" << endl;
	cout << "this contains: << fn(this) << endl" << endl;
	cout << "that contains: << fn(this) << endl" << endl;

	cout << "that contains: " << fn("that") << endl;
	cout << "this contains: " << fn("this") << endl;

	return 0;
}
