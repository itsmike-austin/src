//============================================================================
// Name        : Iterator.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iterator>
#include <typeinfo>

using namespace std;

int main() {
	typedef iterator_traits<int*> traits;

	if ( typeid(traits::iterator_category) == typeid(random_access_iterator_tag) )
		cout << "int* is a random-access iterator" << endl;

	return 0;
}
