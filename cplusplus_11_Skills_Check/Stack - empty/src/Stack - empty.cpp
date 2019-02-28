//============================================================================
// Name        : Stack.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stack>

using namespace std;

int main() {
	stack<int> s;

	cout << "stack.empty() flag: true/false" << endl;

	if ( s.empty() ) cout << "Stack is empty." << endl;

	s.emplace(1);

	if ( !s.empty() ) cout << "Stack is not empty." << endl;

	return 0;
}
