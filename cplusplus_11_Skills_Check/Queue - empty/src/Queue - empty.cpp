//============================================================================
// Name        : Queue.cpp
// Author      : Mike
// Version     :
// Copyright   : (c) ITSinc
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <queue>

using namespace std;

int main() {
	queue<int> q;

	cout << "q.empty() flag: empty queue" << endl;

	if ( q.empty() ) cout << "Queue is empty" << endl;

	cout << "q.push(4);" << endl;

	q.push(4);

	if ( !q.empty() ) cout << "Queue is not empty" << endl;

	return 0;
}
