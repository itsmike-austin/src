//============================================================================
// Name        : Set.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
	set<string> setOfNumbers;

	setOfNumbers.insert("first");
	setOfNumbers.insert("second");
	setOfNumbers.insert("third");

	cout << "Retrieve set elements using iterator: ";
	for(set<string>::iterator it=setOfNumbers.begin() ; it != setOfNumbers.end() ; ++it ) cout << *it << " ";
	cout << endl;

	set<string>::iterator k = setOfNumbers.find("second");

	cout << "Retrieve data using set::find - set.find(\"second\")" << endl;

	if ( k != setOfNumbers.end() )
		cout << *k << " caught from set.find(\"second\")" << endl;
	else
		cout << "set.find(\"second\") not found." << endl;

	k = setOfNumbers.find("fourth");

	if ( k != setOfNumbers.end() )
		cout << *k << " caught fromset.find(\"fourth\")" << endl;
	else
		cout << "set.find(\"fourth\") was not found." << endl;

	cout << "s.erase(first) should remove the first string" << endl;

	setOfNumbers.erase("first");

	cout << "Set of numbers now: ";
	for(set<string>::iterator it = setOfNumbers.begin() ; it != setOfNumbers.end() ; ++it ) cout << *it << " ";
	cout << endl << endl;

	return 0;
}
