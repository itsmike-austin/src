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

	cout << "unordered_set - load_factor -- max_load_factor" << endl;

	cout << "size():            " << us.size() << endl;
	cout << "bucket_count():    " << us.bucket_count() << endl;
	cout << "load_factor():     " << us.load_factor() << endl;
	cout << "max_load_factor(): " << us.max_load_factor() << endl;

	return 0;
}
